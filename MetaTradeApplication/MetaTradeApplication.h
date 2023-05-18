#pragma once
#include <MetaTradeNode/MetaTradeNode.h>
#include <string>

class MetaTradeApplication
{
private:
	std::string private_key{};
	std::string public_key{};
	std::string wallet_address{};
	metatradenode::nodeconfig _cfg{};
	std::unique_ptr<metatradenode::MetaTradeNode> _node;
	static unsigned char hex2byte(char c);
public:
	MetaTradeApplication() = default;
	MetaTradeApplication& operator=(const MetaTradeApplication&) = delete;
	MetaTradeApplication(const MetaTradeApplication&) = delete;

	bool ReadConfig();
	void Init(bool enableMining = true);
	void ReloadNode();
	void Run(bool sync = true);
	long QueryAmount(const char* address, const char* item_id);
	void SubmitTrade(const char* receiver, const char* item_id, long amount);


	static void CreateConfigByStr(const char* pky);
	static void ExportConfig(char* pky);
	static void CreateConfigByRandom();
};

