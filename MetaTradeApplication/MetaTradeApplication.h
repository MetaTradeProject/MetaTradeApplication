#pragma once
#include <MetaTradeNode/BlockChainService.h>
#include <MetaTradeNode/MetaTradeClient.h>
#include <MetaTradeNode/CryptoUtils.h>
#include <MetaTradeNode/BlockChainImpl.h>

class MetaTradeApplication
{
private:
	std::string private_key;
	std::string public_key;
	std::string wallet_address;
	metatradenode::BlockChainService* _node_service_pt{ nullptr };
	metatradenode::MetaTradeClient* _node_client_pt{ nullptr };

	static unsigned char hex2byte(char c);
public:
	static void CreateConfigByStr(const char* pky);
	static void ExportConfig(char* pky);
	static void CreateConfigByRandom();
	bool ReadConfig();
	void Init();
	~MetaTradeApplication();
};

