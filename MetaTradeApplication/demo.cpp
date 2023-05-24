#include "MetaTradePublishApi.h"
#include "MetaTradeApplication.h"

int main() {
	MetaTradeApplication application;
	if (!application.ReadConfig()) {
		application.CreateConfigByRandom();
	}
	application.Init(false);
	std::string address = application.Address();
	application.Run(false);
	Sleep(1000);
	auto a = application.QueryAmount(address.c_str(), "0");
	std::cout << "cash: " << a << std::endl;

	StoreInfo* info;
	uint64_t sz;
	application.QueryStoreInfoList(&info, &sz);

	std::cout << sz << std::endl;

	//bool res = application.SubmitFakeTrade("1DLxqyvwEaEiuqbex97C5UVD93DTeWaXwU", address.c_str(), "1", 1000);
	//std::cout << res << std::endl;
	while (true) {

	}
	return 0;
}