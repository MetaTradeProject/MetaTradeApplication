#include "MetaTradeApplication.h"

constexpr auto pk_path = "./metatrade.pky";
unsigned char magic_numbers[32]{
	0xd3, 0xef, 0xdc, 0x3c, 0x01, 0xa2, 0x5d, 0xc2,
	0xb3, 0x89, 0x73, 0x50, 0xd4, 0x6d, 0xee, 0x69,
	0x1c, 0xc4, 0xfb, 0x4c, 0x03, 0x05, 0x21, 0x63,
	0x83, 0x53, 0xc5, 0x5f, 0x46, 0xa1, 0x07, 0xed
};

bool MetaTradeApplication::ReadConfig() {
	std::ifstream is(pk_path);
	if (is.good()) {
		unsigned char encoded[32]{};
		is.read((char*)encoded, 32);

		for (size_t i = 0; i < 32; i++) {
			encoded[i] = (encoded[i] ^ magic_numbers[i]);
		}

		std::stringstream ss;
		for (size_t i = 0; i < 32; i++) {
			char c[5];
			sprintf_s(c, "%02x", encoded[i]);
			ss << c;
		}

		this->private_key = ss.str();
		is.close();
		return true;
	}
	else {
		is.close();
		return false;
	}
}

void MetaTradeApplication::Init(bool enableMining) {
	if (this->private_key.size() != 64) {
		std::cerr << "Private Key not set...\n";
		return;
	}
	char* public_key_str;
	char* address_str;
	CryptoUtils::GeneratePublic(this->private_key.c_str(), public_key_str, address_str);
	this->public_key = public_key_str;
	this->wallet_address = address_str;

	// node
	strcpy_s(_cfg.address, 35, this->wallet_address.c_str());
	strcpy_s(_cfg.prikey, 65, this->private_key.c_str());
	strcpy_s(_cfg.pubkey, 67, this->public_key.c_str());
	_cfg.mining = enableMining;
	this->_node = std::make_unique<metatradenode::MetaTradeNode>(_cfg);
	this->_node->init();
}

void MetaTradeApplication::ReloadNode(){
	this->_node->reload();
}

void MetaTradeApplication::Run(bool sync){
	this->_node->run(sync);
}

long long MetaTradeApplication::QueryAmount(const char* address, const char* item_id){
	return this->_node->queryAmount(address, item_id);
}

long long MetaTradeApplication::QueryTransitAmount(const char* address, const char* item_id){
	return this->_node->queryTransitAmount(address, item_id);
}

void MetaTradeApplication::SubmitTrade(const char* receiver, const char* item_id, long amount){
	this->_node->submitTrade(receiver, item_id, amount);
}

void MetaTradeApplication::CreateConfigByStr(const char* pky){
	std::ofstream os(pk_path);
	if (os.good()) {
		std::cerr << "pky existes...\n";
		return;
	}

	unsigned char buffer[32]{ 0 };

	if (strlen(pky) != 64) {
		std::cerr << "pky size need to equal to 64 ...\n";
		return;
	}
	else {
		for (size_t i = 0; i < 32; i++) {
			unsigned char fir = hex2byte(pky[2 * i]);
			unsigned char sec = hex2byte(pky[2 * i + 1]);
			buffer[i] = (fir << 4) | sec;
		}
	}

	for (size_t i = 0; i < 32; i++) {
		buffer[i] = (buffer[i] ^ magic_numbers[i]);
	}

	os.write((char*)buffer, 32);
	os.close();
}

void MetaTradeApplication::CreateConfigByRandom() {
	std::ofstream os(pk_path);
	if (os.good()) {
		std::cerr << "pky existes...\n";
		return;
	}

	//Generate new private key and write file;
	unsigned char pky[32]{ 0 };

	//Random
#if defined(_WIN32)
	BCryptGenRandom(0, pky, 32, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
#elif defined(__linux__) || defined(__FreeBSD__)
	getrandom(pky, 32, 0);
#elif defined(__APPLE__) || defined(__OpenBSD__)
	getentropy(pky, 32);
#endif

	for (size_t i = 0; i < 32; i++) {
		pky[i] = (pky[i] ^ magic_numbers[i]);
	}

	os.write((char*)pky, 32);
	os.close();
}

void MetaTradeApplication::ExportConfig(char* pky){
	std::ifstream is(pk_path);
	if (is.good()) {
		unsigned char encoded[32];
		is.read((char*)encoded, 32);

		for (size_t i = 0; i < 32; i++) {
			encoded[i] = (encoded[i] ^ magic_numbers[i]);
		}

		std::stringstream ss;
		for (size_t i = 0; i < 32; i++) {
			char c[5];
			sprintf_s(c, "%02x", encoded[i]);
			ss << c;
		}

		pky = new char[65];
		strcpy_s(pky, 65, ss.str().c_str());
	}
	else {
		pky = nullptr;
	}
	is.close();
}

unsigned char MetaTradeApplication::hex2byte(char c)
{
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	return 0;
}