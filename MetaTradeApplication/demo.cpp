#include "MetaTradePublishApi.h"

int main() {
	//MetaTradeApplication application;
	//if (!application.Check_n_ReadConfig()) {
	//	MetaTradeApplication::RegisterNode();
	//	application.Check_n_ReadConfig();
	//}
	////application.Init();
	MetaTradePublishApi myapi(U("http://127.0.0.1:7286/"));

	myapi.getStoreInfoList()
	.then([](std::vector<std::shared_ptr<StoreInfo>> res) {
		for (auto& info : res) {
			std::cout << info->id << info->address << info->description << std::endl;
		}
	}).wait();

	myapi.getStoreInfo("123456")
	.then([](std::shared_ptr<StoreInfo> pt) {
		std::cout << pt->id << std::endl;
	}).wait();

	myapi.getItemInfoList("123456")
	.then([](std::vector<std::shared_ptr<ItemInfo>> res) {
		for (auto& info : res) {
			std::cout << info->id << info->amount << info->description << std::endl;
		}
	}).wait();
	return 0;
}