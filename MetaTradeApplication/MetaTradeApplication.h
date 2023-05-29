#pragma once
#include <MetaTradeNode/MetaTradeNode.h>
#include "MetaTradePublishModel.h"
#include "MetaTradePublishApi.h"
#include <string>

/// <summary>
/// MetaTrade����������
/// </summary>
class META_APP_PUBLIC MetaTradeApplication
{
private:
	std::string private_key{};
	std::string public_key{};
	std::string wallet_address{};
	metatradenode::nodeconfig _cfg{};
	std::unique_ptr<metatradenode::MetaTradeNode> _node;
	std::unique_ptr<MetaTradePublishApi> _api{};
	static unsigned char hex2byte(char c);
public:
	MetaTradeApplication() = default;
	MetaTradeApplication& operator=(const MetaTradeApplication&) = delete;
	MetaTradeApplication(const MetaTradeApplication&) = delete;

	/// <summary>
	/// ��ָ���ļ���ȡ˽Կ
	/// </summary>
	bool ReadConfig();

	/// <summary>
	/// ��ʼ������
	/// </summary>
	/// <param name='force'>�Ƿ�ǿ�������ػ���</param>
	/// <param name='enableMining'>�Ƿ�����Mining����</param>
	/// <param name='publisher'>���ͻص�����</param>
	void Init(bool force = true, bool enableMining = false, metatradenode::MiningPublisher* publisher = nullptr);

	/// <summary>
	/// ��ȡ�ڵ��ַ����Ҫ�ڵ���Init��ʹ��
	/// </summary>
	/// <returns>�ڵ��ַ</returns>
	const char* Address();

	/// <summary>
	/// ��������Node���񣬼�ͬ������Sync��Ϣ
	/// </summary>
	void ReloadNode();

	/// <summary>
	/// ���з���
	/// </summary>
	/// <param name='sync'>ͬ��/�첽���з���</param>
	void Run(bool sync = true);
	
	/// <summary>
	/// ��ѯ��ǰ�������
	/// </summary>
	/// <param name='address'>ָ��Ǯ����ַ</param>
	/// <param name='item_id'>ָ����Ʒid</param>
	/// <returns>��ѯ�����������ڸ���Ʒ����Ϊ0</returns>
	long long QueryAmount(const char* address, const char* item_id);
	
	/// <summary>
	/// ��ѯ��ǰ��;�������ο��������������������
	/// </summary>
	/// <param name='address'>ָ��Ǯ����ַ</param>
	/// <param name='item_id'>ָ����Ʒid</param>
	/// <returns>��ѯ����;���������ڸ���Ʒ����Ϊ0</returns>
	long long QueryTransitAmount(const char* address, const char* item_id);

	/// <summary>
	/// ��ѯ���������˵���Ϣ
	/// </summary>
	/// <param name='address'>ָ��Ǯ����ַ</param>
	/// <param name='bills'>Output - ��ѯ���</param>
	/// <param name='sz'>Output - ��ѯ�������</param>
	void QueryBills(const char* address, metatradenode::Bill** bills, uint64_t* sz);

	/// <summary>
	/// ��ѯ��ǰ��;�˵��������ο������������������˵�
	/// </summary>
	/// <param name='address'>ָ��Ǯ����ַ</param>
	/// <param name='bills'>Output - ��ѯ���</param>
	/// <param name='sz'>Output - ��ѯ�������</param>
	void QueryTransitBills(const char* address, metatradenode::Bill** bills, uint64_t* sz);

	/// <summary>
	/// ��ѯ�����̵���Ϣ
	/// </summary>
	/// <param name='store_list'>Output - ��ѯ���</param>
	/// <param name='sz'>Output - ��ѯ�������</param>
	void QueryStoreInfoList(StoreInfo** store_list, uint64_t* sz);

	/// <summary>
	/// ��ѯָ���̵��������Ʒ��Ϣ
	/// </summary>
	/// <param name='item_list'>Output - ��ѯ���</param>
	/// <param name='sz'>Output - ��ѯ�������</param>
	/// <param name='address'>ָ���̵��ַ</param>
	void QueryItemInfoList(ItemInfo** item_list, uint64_t* sz, const char* address);

	/// <summary>
	/// ��ѯָ���̵����Ϣ
	/// </summary>
	/// <param name='store_info'>Output - ��ѯ���</param>
	/// <param name='address'>ָ���̵��ַ</param>
	void QueryStoreInfo(StoreInfo* store_info, const char* address);

	/// <summary>
	/// ��ѯָ���̵��ָ����Ʒ��Ϣ
	/// </summary>
	/// <param name='item_info'>Output - ��ѯ���</param>
	/// <param name='address'>ָ���̵��ַ</param>
	/// <param name='item_id'>ָ����Ʒid</param>
	void QueryItemInfo(ItemInfo* item_info, const char* address, const char* item_id);

	/// <summary>
	/// �û������ύһ��������Ϣ��ΪSender������ʵ��Sender֧����Ҫ����Commission
	/// </summary>
	/// <param name='receiver'>���շ���Ǯ����ַ</param>
	/// <param name='item_id'>���׵���Ʒid</param>
	/// <param name='amount'>���׵�����</param>
	void SubmitTrade(const char* receiver, const char* item_id, long long amount);

	/// <summary>
	/// �ͻ����߼��ύһ��FakeTrade��Ϣ���û�ΪReceiver��������Commission
	/// </summary>
	/// <param name='store_address'>�̵�ĵ�ַ</param>
	/// <param name='receiver'>���շ���Ǯ����ַ</param>
	/// <param name='item_id'>���׵���Ʒid</param>
	/// <param name='amount'>���׵�����</param>
	/// <returns>�Ƿ��ύ�ɹ�</returns>
	bool SubmitFakeTrade(const char* store_address, const char* receiver_address, const char* item_id, long long amount);

	/// <summary>
	/// �ͻ����߼��ύһ����ʱFakeTrade��Ϣ���û�ΪReceiver��������Commission
	/// </summary>
	/// <param name='cron'>Cron ���ʽ</param>
	/// <param name='store_address'>�̵�ĵ�ַ</param>
	/// <param name='receiver_address'>���շ���Ǯ����ַ</param>
	/// <param name='item_id'>���׵���Ʒid</param>
	/// <param name='amount'>���׵�����</param>
	/// <param name='key'>Output - �ύ�ɹ����صĶ�ʱ����Ψһ��ʶ</param>
	void SubmitCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount, char* key);

	/// <summary>
	/// �ͻ����߼�ɾ��һ����ʱFakeTrade��Ϣ
	/// </summary>
	/// <param name='store_address'>�̵�ĵ�ַ</param>
	/// <param name='item_id'>���׵���Ʒid</param>
	/// <param name='key'>ָ��ɾ���Ķ�ʱ����Ψһ��ʶ</param>
	bool DeleteCronTrade(const char* store_address, const char* item_id, const char* key);

	/// <summary>
	/// �ͻ����߼��޸�һ����ʱFakeTrade��Ϣ
	/// </summary>
	/// <param name='cron'>Cron ���ʽ</param>
	/// <param name='store_address'>�̵�ĵ�ַ</param>
	/// <param name='receiver_address'>���շ���Ǯ����ַ</param>
	/// <param name='item_id'>���׵���Ʒid</param>
	/// <param name='amount'>���׵�����</param>
	/// <param name='key'>ָ���޸ĵĶ�ʱ����Ψһ��ʶ</param>
	/// <returns>�Ƿ��޸ĳɹ�</returns>
	bool PutCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount, const char* key);

	/// <summary>
	/// ���ⲿ����˽Կ���ã�д�������ļ��У���˽Կ���Ϸ����򷵻�
	/// </summary>
	/// <param name='pky'>Input - ��Ҫ�����˽Կ</param>
	static void CreateConfigByStr(const char* pky);

	/// <summary>
	/// ����˽Կ����
	/// </summary>
	/// <param name='pky'>Output - ������˽Կ�ַ���</param>
	static void ExportConfig(char* pky);

	/// <summary>
	/// �ڱ�����������㷨�������˽Կ����д�������ļ��У������������ļ����ڣ��򷵻�
	/// </summary>
	/// <remarks>
	/// �ڱ��������ļ�������ʱ�����������
	/// </remarks>
	static void CreateConfigByRandom();
};

