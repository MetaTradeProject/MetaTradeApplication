#include "MetaTradePublishApi.h"
#include <cpprest/json.h>

pplx::task<std::vector<std::shared_ptr<StoreInfo>>> MetaTradePublishApi::getStoreInfoList(){
    web::http::uri_builder builder(U("/meta-trade/stores"));

    return this->_client.request(web::http::methods::GET, builder.to_string())
    .then([this](web::http::http_response response){
        std::vector<std::shared_ptr<StoreInfo>> res;
        web::json::value jsonObject;
        if(response.status_code() == web::http::status_codes::OK){
            response.headers().set_content_type(utility::conversions::to_string_t("application/json"));
            jsonObject = response.extract_json().get();     
            for(auto& store_item: jsonObject.as_array()){
                std::shared_ptr<StoreInfo> pt = std::make_shared<StoreInfo>();
                strcpy_s(pt->address, 35, utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("address")).as_string()).c_str());
                strcpy_s(pt->id, 10, utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("id")).as_string()).c_str());
                strcpy_s(pt->description, 64, utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("description")).as_string()).c_str());

                res.push_back(pt);
            }
        }
        return res;
    });
}

pplx::task<std::shared_ptr<StoreInfo>> MetaTradePublishApi::getStoreInfo(const char* address){
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/meta-trade/store/").append(address).append("/info")));

    return this->_client.request(web::http::methods::GET, builder.to_string())
    .then([this](web::http::http_response response){
        std::shared_ptr<StoreInfo> pt = std::make_shared<StoreInfo>();
        web::json::value store_item;
        if(response.status_code() == web::http::status_codes::OK){
            response.headers().set_content_type(utility::conversions::to_string_t("application/json"));
            store_item = response.extract_json().get();     
            strcpy_s(pt->address, 35, utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("address")).as_string()).c_str());
            strcpy_s(pt->id, 10, utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("id")).as_string()).c_str());
            strcpy_s(pt->description, 64, utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("description")).as_string()).c_str());
        }
        return pt;
    });
}

pplx::task<std::vector<std::shared_ptr<ItemInfo>>> MetaTradePublishApi::getItemInfoList(const char* address){
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/meta-trade/store/").append(address).append("/items")));

    return this->_client.request(web::http::methods::GET, builder.to_string())
    .then([this](web::http::http_response response){
        std::vector<std::shared_ptr<ItemInfo>> res;
        web::json::value jsonObject;
        if(response.status_code() == web::http::status_codes::OK){
            response.headers().set_content_type(utility::conversions::to_string_t("application/json"));
            jsonObject = response.extract_json().get();     
            for(auto& item: jsonObject.as_array()){
                std::shared_ptr<ItemInfo> pt = std::make_shared<ItemInfo>();
                strcpy_s(pt->id, 10, utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("id")).as_string().c_str()).c_str());
                pt->amount = item.at(utility::conversions::to_string_t("amount")).as_integer();
                strcpy_s(pt->store_address, 35, utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("store_address")).as_string().c_str()).c_str());
                strcpy_s(pt->description, 64, utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("description")).as_string()).c_str());

                res.push_back(pt);
            }
        }
        return res;
    });
}

pplx::task<std::shared_ptr<ItemInfo>> MetaTradePublishApi::getItemInfo(const char* address, const char* item_id) {
    web::http::http_request request;
    request.set_method(utility::conversions::to_string_t("GET"));
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/store/").append(address).append("/item/").append(item_id)));
    request.set_request_uri(builder.to_uri());

    return this->_client.request(request)
    .then([this](web::http::http_response response) {
        std::shared_ptr<ItemInfo> pt = std::make_shared<ItemInfo>();
        web::json::value item;
        if (response.status_code() == web::http::status_codes::OK) {
            response.headers().set_content_type(utility::conversions::to_string_t("application/json"));
            item = response.extract_json().get();
            strcpy_s(pt->id, 10, utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("id")).as_string().c_str()).c_str());
            pt->amount = item.at(utility::conversions::to_string_t("amount")).as_integer();
            strcpy_s(pt->store_address, 35, utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("store_address")).as_string().c_str()).c_str());
            strcpy_s(pt->description, 64, utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("description")).as_string()).c_str());
        }
        return pt;
    });
}

pplx::task<web::http::http_response> MetaTradePublishApi::submitFakeTrade(const char* store_address, const char* receiver_address, const char* item_id, long long amount){
    web::http::http_request request;
    request.set_method(utility::conversions::to_string_t("POST"));
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/store/").append(store_address).append("/item/").append(item_id).append("/simple-trade")));
    request.set_request_uri(builder.to_uri());
    web::json::value simpleRequest;
    simpleRequest[L"receiverAddress"] = web::json::value::string(utility::conversions::to_string_t(receiver_address));
    simpleRequest[L"amount"] = web::json::value::number(amount);
    request.set_body(simpleRequest);

    return this->_client.request(request);
}

pplx::task<web::http::http_response> MetaTradePublishApi::submitCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount){
    web::http::http_request request;
    request.set_method(utility::conversions::to_string_t("POST"));
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/store/").append(store_address).append("/item/").append(item_id).append("/cron-trade")));
    request.set_request_uri(builder.to_uri());
    web::json::value cronRequest;
    cronRequest[L"cron"] = web::json::value::string(utility::conversions::to_string_t(cron));
    cronRequest[L"receiverAddress"] = web::json::value::string(utility::conversions::to_string_t(receiver_address));
    cronRequest[L"amount"] = web::json::value::number(amount);
    request.set_body(cronRequest);

    return this->_client.request(request);
}

pplx::task<web::http::http_response> MetaTradePublishApi::deleteCronTrade(const char* store_address, const char* item_id, const char* key){
    web::http::http_request request;
    request.set_method(utility::conversions::to_string_t("DELETE"));
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/store/").append(store_address).append("/item/").append(item_id).append("/cron-trade/").append(key)));
    request.set_request_uri(builder.to_uri());

    return this->_client.request(request);
}

pplx::task<web::http::http_response> MetaTradePublishApi::putCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount, const char* key){
    web::http::http_request request;
    request.set_method(utility::conversions::to_string_t("PUT"));
    web::http::uri_builder builder(utility::conversions::to_string_t(std::string("/store/").append(store_address).append("/item/").append(item_id).append("/cron-trade/").append(key)));
    request.set_request_uri(builder.to_uri());
    web::json::value cronRequest;
    cronRequest[L"cron"] = web::json::value::string(utility::conversions::to_string_t(cron));
    cronRequest[L"receiverAddress"] = web::json::value::string(utility::conversions::to_string_t(receiver_address));
    cronRequest[L"amount"] = web::json::value::number(amount);
    request.set_body(cronRequest);

    return this->_client.request(request);
}
