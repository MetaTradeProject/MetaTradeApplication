#pragma once
#include <string>

struct ItemInfo{
    char id[10];
    long long amount;
    char store_address[35];
    char description[64];
};

struct StoreInfo{
    char address[35];
    char id[10];
    char description[64];
};