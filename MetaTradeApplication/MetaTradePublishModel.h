#pragma once
#include <string>

struct ItemInfo{
    std::string id;
    long amount;
    std::string store_address;
    std::string description;
};

struct StoreInfo{
    std::string address;
    std::string id;
    std::string description;
};