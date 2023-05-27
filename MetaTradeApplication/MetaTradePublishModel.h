#pragma once
#include <string>

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__
#define META_APP_PUBLIC   __declspec(dllexport)
#else
#define META_APP_PUBLIC 
#endif


/// <summary>
/// 物品属性信息
/// </summary>
struct META_APP_PUBLIC ItemInfo{

    /// <summary>
    /// 该物品的id，现阶段均为数字，Coin默认为0
    /// </summary>
    char id[10];

    /// <summary>
    /// 该物品的价格（以Coin计）
    /// </summary>
    long long amount;

    /// <summary>
    /// 该物品所在的商店的地址
    /// </summary>
    char store_address[35];

    /// <summary>
    /// 额外描述字段
    /// </summary>
    char description[64];
};

/// <summary>
/// 商店属性信息
/// </summary>
struct META_APP_PUBLIC StoreInfo{

    /// <summary>
    /// 商店地址
    /// </summary>
    char address[35];

    /// <summary>
    /// 商店用于其他地方的标识id，在MetaTrade中不作解释
    /// </summary>
    char id[10];

    /// <summary>
    /// 额外描述字段
    /// </summary>
    char description[64];
};

struct SimpleTradeResponse {
    std::string res;
};