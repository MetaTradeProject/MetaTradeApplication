#include "MetaTradePublishApi.h"
#include "MetaTradeApplication.h"

class Test : public metatradenode::MiningPublisher {
	void PublishStart(int proveLevel) {
		std::cout << proveLevel << std::endl;
	};
	void PublishFinished(int your_proof) {
		std::cout << your_proof << std::endl;
	};
};

int main() {
	MetaTradeApplication application;
	if (!application.ReadConfig()) {
		application.CreateConfigByRandom();
	}
	if (!application.ReadConfig()) {
		std::cerr << "error\n";
		return 0;
	}
	application.Init(true, true, new Test());
	std::string address = application.Address();
	application.Run(false);
	Sleep(1000);
	auto a = application.QueryAmount(address.c_str(), "0");
	std::cout << "cash: " << a << std::endl;

	//StoreInfo* info;
	//uint64_t sz;
	//application.QueryStoreInfoList(&info, &sz);


	//application.SubmitTrade(info[0].address, "0", 8900);
	//application.SubmitFakeTrade(info[0].address, address.c_str(), "1", 100);


	//for (int i = 0; i < 10; i++) { 
	//	std::cout << i << std::endl;
	//	application.SubmitTrade(info[0].address, "0", 8900); 
	//	Sleep(200);
	//}

	//bool res = application.SubmitFakeTrade("1DLxqyvwEaEiuqbex97C5UVD93DTeWaXwU", address.c_str(), "1", 1000);
	//std::cout << res << std::endl;
	while (true) {

	}
	return 0;
}