#include "MetaTradeApplication.h"

int main() {
	MetaTradeApplication application;
	if (!application.Check_n_ReadConfig()) {
		MetaTradeApplication::RegisterNode();
		application.Check_n_ReadConfig();
	}
	//application.Init();
}