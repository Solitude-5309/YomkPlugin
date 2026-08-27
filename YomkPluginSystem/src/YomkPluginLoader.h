#pragma once
#include "YomkPluginMsgs.h"
#include "../include/YomkPlugin.h" /* 编译期相对引用；下游按安装布局 <YomkPluginSystem/YomkPlugin.h> 引用 */

#include <map>
#include <mutex>
#include <vector>

using namespace yomk;

/*
 * YomkPluginLoader：插件加载机制层
 * 纯加载机制，不登记插件、不拥有实例、不管命名。仅持有两种机制状态：
 *  - 句柄表：libId -> { dlopen 句柄, 三个导出函数指针 }（dlclose 的唯一凭据）
 *  - 实例存活表：libId -> weak_ptr 列表（仅判活不延长生命周期，作用等同引用计数保护）
 */
class YomkPluginLoader : public YomkService
{
public:
    YomkPluginLoader(YomkServer *server);
    virtual ~YomkPluginLoader() {}
    virtual int init() override;

private:
    struct LoadedLib
    {
        void *handle = nullptr;
        YomkPluginMetaFunc metaFn = nullptr;
        YomkPluginCreateInstanceFunc createFn = nullptr;
        YomkPluginDeleteInstanceFunc deleteFn = nullptr;
    };

    /* 请求接口 */
    YomkResponse loadLib(YomkPkgPtr pkg);        /* PluginPath -> String libId */
    YomkResponse unloadLib(YomkPkgPtr pkg);      /* String libId -> ok（有存活实例拒绝） */
    YomkResponse meta(YomkPkgPtr pkg);           /* String libId -> PluginMeta */
    YomkResponse create(YomkPkgPtr pkg);         /* CreateReq -> PluginInstance */
    YomkResponse deleteInstance(YomkPkgPtr pkg); /* PluginInstance -> ok */
    YomkResponse version(YomkPkgPtr pkg);        /* -> String */
    /* 内省接口 */
    YomkResponse infoLibs(YomkPkgPtr pkg); /* -> StringArray */
    YomkResponse infoLib(YomkPkgPtr pkg);  /* String libId -> String 元信息行 */
    YomkResponse infoAll(YomkPkgPtr pkg);  /* -> String 全量 dump */

    /* 内部辅助（调用方已持锁） */
    void purgeDead(const std::string &libId);
    int aliveCount(const std::string &libId);
    std::string libInfoLine(const std::string &libId);

    std::mutex m_mutex;
    std::map<std::string, LoadedLib> m_libs;                                        /* 句柄表 */
    std::map<std::string, std::vector<std::weak_ptr<YomkPluginInterface>>> m_alive; /* 存活表 */
};
