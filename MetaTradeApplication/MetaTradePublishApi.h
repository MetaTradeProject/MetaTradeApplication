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
    pplx::task<web::http::http_response> submitFakeTrade(const char* store_address, const char* receiver_address, const char* item_id, long long amount);
    pplx::task<web::http::http_response> submitCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount);
    pplx::task<web::http::http_response> deleteCronTrade(const char* store_address, const char* item_id, const char* key);
    pplx::task<web::http::http_response> putCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount, const char* key);
};