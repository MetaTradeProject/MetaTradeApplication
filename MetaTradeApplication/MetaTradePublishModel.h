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
/// ��Ʒ������Ϣ
/// </summary>
struct META_APP_PUBLIC ItemInfo{

    /// <summary>
    /// ����Ʒ��id���ֽ׶ξ�Ϊ���֣�CoinĬ��Ϊ0
    /// </summary>
    char id[10];

    /// <summary>
    /// ����Ʒ�ļ۸���Coin�ƣ�
    /// </summary>
    long long amount;

    /// <summary>
    /// ����Ʒ���ڵ��̵�ĵ�ַ
    /// </summary>
    char store_address[35];

    /// <summary>
    /// ���������ֶ�
    /// </summary>
    char description[64];
};

/// <summary>
/// �̵�������Ϣ
/// </summary>
struct META_APP_PUBLIC StoreInfo{

    /// <summary>
    /// �̵��ַ
    /// </summary>
    char address[35];

    /// <summary>
    /// �̵����������ط��ı�ʶid����MetaTrade�в�������
    /// </summary>
    char id[10];

    /// <summary>
    /// ���������ֶ�
    /// </summary>
    char description[64];
};

struct SimpleTradeResponse {
    std::string res;
};