#pragma once
#include <MetaTradeNode/MetaTradeNode.h>
#include "MetaTradePublishModel.h"
#include "MetaTradePublishApi.h"
#include <string>

/// <summary>
/// MetaTrade服务的总入口
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
	/// 从指定文件读取私钥
	/// </summary>
	bool ReadConfig();

	/// <summary>
	/// 初始化服务
	/// </summary>
	/// <param name='force'>是否强制清理本地缓存</param>
	/// <param name='enableMining'>是否启动Mining服务</param>
	/// <param name='publisher'>推送回调函数</param>
	void Init(bool force = true, bool enableMining = false, metatradenode::MiningPublisher* publisher = nullptr);

	/// <summary>
	/// 获取节点地址，需要在调用Init后使用
	/// </summary>
	/// <returns>节点地址</returns>
	const char* Address();

	/// <summary>
	/// 重新启动Node服务，即同步区块Sync消息
	/// </summary>
	void ReloadNode();

	/// <summary>
	/// 运行服务
	/// </summary>
	/// <param name='sync'>同步/异步运行服务</param>
	void Run(bool sync = true);
	
	/// <summary>
	/// 查询当前上链余额
	/// </summary>
	/// <param name='address'>指定钱包地址</param>
	/// <param name='item_id'>指定物品id</param>
	/// <returns>查询的余额，若不存在该物品，则为0</returns>
	long long QueryAmount(const char* address, const char* item_id);
	
	/// <summary>
	/// 查询当前在途余额，仅供参考，不代表最终上链余额
	/// </summary>
	/// <param name='address'>指定钱包地址</param>
	/// <param name='item_id'>指定物品id</param>
	/// <returns>查询的在途余额，若不存在该物品，则为0</returns>
	long long QueryTransitAmount(const char* address, const char* item_id);

	/// <summary>
	/// 查询至今所有账单信息
	/// </summary>
	/// <param name='address'>指定钱包地址</param>
	/// <param name='bills'>Output - 查询结果</param>
	/// <param name='sz'>Output - 查询结果条数</param>
	void QueryBills(const char* address, metatradenode::Bill** bills, uint64_t* sz);

	/// <summary>
	/// 查询当前在途账单，仅供参考，不代表最终上链账单
	/// </summary>
	/// <param name='address'>指定钱包地址</param>
	/// <param name='bills'>Output - 查询结果</param>
	/// <param name='sz'>Output - 查询结果条数</param>
	void QueryTransitBills(const char* address, metatradenode::Bill** bills, uint64_t* sz);

	/// <summary>
	/// 查询所有商店信息
	/// </summary>
	/// <param name='store_list'>Output - 查询结果</param>
	/// <param name='sz'>Output - 查询结果条数</param>
	void QueryStoreInfoList(StoreInfo** store_list, uint64_t* sz);

	/// <summary>
	/// 查询指定商店的所有物品信息
	/// </summary>
	/// <param name='item_list'>Output - 查询结果</param>
	/// <param name='sz'>Output - 查询结果条数</param>
	/// <param name='address'>指定商店地址</param>
	void QueryItemInfoList(ItemInfo** item_list, uint64_t* sz, const char* address);

	/// <summary>
	/// 查询指定商店的信息
	/// </summary>
	/// <param name='store_info'>Output - 查询结果</param>
	/// <param name='address'>指定商店地址</param>
	void QueryStoreInfo(StoreInfo* store_info, const char* address);

	/// <summary>
	/// 查询指定商店的指定物品信息
	/// </summary>
	/// <param name='item_info'>Output - 查询结果</param>
	/// <param name='address'>指定商店地址</param>
	/// <param name='item_id'>指定物品id</param>
	void QueryItemInfo(ItemInfo* item_info, const char* address, const char* item_id);

	/// <summary>
	/// 用户主动提交一条交易信息（为Sender方），实际Sender支付的要加上Commission
	/// </summary>
	/// <param name='receiver'>接收方的钱包地址</param>
	/// <param name='item_id'>交易的物品id</param>
	/// <param name='amount'>交易的数量</param>
	void SubmitTrade(const char* receiver, const char* item_id, long long amount);

	/// <summary>
	/// 客户端逻辑提交一条FakeTrade信息（用户为Receiver方），无Commission
	/// </summary>
	/// <param name='store_address'>商店的地址</param>
	/// <param name='receiver'>接收方的钱包地址</param>
	/// <param name='item_id'>交易的物品id</param>
	/// <param name='amount'>交易的数量</param>
	/// <returns>是否提交成功</returns>
	bool SubmitFakeTrade(const char* store_address, const char* receiver_address, const char* item_id, long long amount);

	/// <summary>
	/// 客户端逻辑提交一条定时FakeTrade信息（用户为Receiver方），无Commission
	/// </summary>
	/// <param name='cron'>Cron 表达式</param>
	/// <param name='store_address'>商店的地址</param>
	/// <param name='receiver_address'>接收方的钱包地址</param>
	/// <param name='item_id'>交易的物品id</param>
	/// <param name='amount'>交易的数量</param>
	/// <param name='key'>Output - 提交成功返回的定时任务唯一标识</param>
	void SubmitCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount, char* key);

	/// <summary>
	/// 客户端逻辑删除一条定时FakeTrade信息
	/// </summary>
	/// <param name='store_address'>商店的地址</param>
	/// <param name='item_id'>交易的物品id</param>
	/// <param name='key'>指定删除的定时任务唯一标识</param>
	bool DeleteCronTrade(const char* store_address, const char* item_id, const char* key);

	/// <summary>
	/// 客户端逻辑修改一条定时FakeTrade信息
	/// </summary>
	/// <param name='cron'>Cron 表达式</param>
	/// <param name='store_address'>商店的地址</param>
	/// <param name='receiver_address'>接收方的钱包地址</param>
	/// <param name='item_id'>交易的物品id</param>
	/// <param name='amount'>交易的数量</param>
	/// <param name='key'>指定修改的定时任务唯一标识</param>
	/// <returns>是否修改成功</returns>
	bool PutCronTrade(const char* cron, const char* store_address, const char* receiver_address, const char* item_id, long long amount, const char* key);

	/// <summary>
	/// 从外部导入私钥配置，写入配置文件中，若私钥不合法，则返回
	/// </summary>
	/// <param name='pky'>Input - 需要导入的私钥</param>
	static void CreateConfigByStr(const char* pky);

	/// <summary>
	/// 导出私钥配置
	/// </summary>
	/// <param name='pky'>Output - 导出的私钥字符串</param>
	static void ExportConfig(char* pky);

	/// <summary>
	/// 在本地由随机数算法随机生成私钥，并写入配置文件中，若本地配置文件存在，则返回
	/// </summary>
	/// <remarks>
	/// 在本地配置文件不存在时调用这个函数
	/// </remarks>
	static void CreateConfigByRandom();
};

