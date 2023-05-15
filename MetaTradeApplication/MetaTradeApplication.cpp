#include "MetaTradeApplication.h"

constexpr auto pk_path = "./metatrade.pky";
unsigned char magic_numbers[32]{
	0xd3, 0xef, 0xdc, 0x3c, 0x01, 0xa2, 0x5d, 0xc2,
	0xb3, 0x89, 0x73, 0x50, 0xd4, 0x6d, 0xee, 0x69,
	0x1c, 0xc4, 0xfb, 0x4c, 0x03, 0x05, 0x21, 0x63,
	0x83, 0x53, 0xc5, 0x5f, 0x46, 0xa1, 0x07, 0xed
};

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

bool MetaTradeApplication::ReadConfig()
{
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

		this->private_key = ss.str();
		return true;
	}
	else {
		return false;
	}
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
		strncpy(pky, ss.str().c_str(), 64);
		pky[64] = '\0';
	}
	else {
		pky = nullptr;
	}
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
}

void MetaTradeApplication::Init() {
	if (this->private_key.size() != 64) {
		std::cerr << "Private Key not set...\n";
		return;
	}
	char* public_key_str;
	char* address_str;
	CryptoUtils::GeneratePublic(this->private_key.c_str(), public_key_str, address_str);
	this->public_key = public_key_str;
	this->wallet_address = address_str;
	_node_client_pt = new metatradenode::MetaTradeClient(wallet_address.c_str());
	_node_service_pt = new BlockChainImpl();
	_node_client_pt->RegisterService(_node_service_pt);
	_node_service_pt->RegisterClient(_node_client_pt);
}

MetaTradeApplication::~MetaTradeApplication() {
	if (_node_client_pt != nullptr) {
		_node_client_pt->Disconnect();
		delete _node_client_pt;
		if (_node_service_pt != nullptr) {
			delete _node_service_pt;
		}
	}
}
