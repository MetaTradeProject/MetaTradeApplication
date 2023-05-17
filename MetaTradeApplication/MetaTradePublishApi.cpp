#include "MetaTradePublishApi.h"

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
                pt->address = utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("address")).as_string());
                pt->id = utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("id")).as_string());
                pt->description = utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("description")).as_string());

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
            pt->address = utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("address")).as_string());
            pt->id = utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("id")).as_string());
            pt->description = utility::conversions::to_utf8string(store_item.at(utility::conversions::to_string_t("description")).as_string());
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
                pt->id = utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("id")).as_string().c_str());
                pt->amount = item.at(utility::conversions::to_string_t("amount")).as_double();
                pt->store_address = utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("store_address")).as_string());
                pt->description = utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("description")).as_string());

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
            pt->id = utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("id")).as_string());
            pt->amount = item.at(utility::conversions::to_string_t("amount")).as_double();
            pt->store_address = utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("store_address")).as_string());
            pt->description = utility::conversions::to_utf8string(item.at(utility::conversions::to_string_t("description")).as_string());
        }
        return pt;
    });
}
