#pragma once
#include <cpprest/http_client.h>
#include <vector>
#include <memory>
#include "MetaTradePublishModel.h"

class MetaTradePublishApi {
private:
    web::http::client::http_client _client;
public:
    MetaTradePublishApi(const web::uri& base_uri) : _client(base_uri) {};
    pplx::task<std::vector<std::shared_ptr<StoreInfo>>> getStoreInfoList();
    pplx::task<std::shared_ptr<StoreInfo>> getStoreInfo(const char* address);
    pplx::task<std::vector<std::shared_ptr<ItemInfo>>> getItemInfoList(const char* address);
    pplx::task<std::shared_ptr<ItemInfo>> getItemInfo(const char* address, const char* item_id);
};