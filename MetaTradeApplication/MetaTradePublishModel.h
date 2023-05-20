#pragma once
#include <string>

/// <summary>
/// ��Ʒ������Ϣ
/// </summary>
struct ItemInfo{

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
struct StoreInfo{

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