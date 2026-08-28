#pragma once
#include <memory>
#include <string>
#include <vector>

#include <YomkServer/YomkAPI.h>
#include "YomkPluginInterface.h"
#include "YomkPluginMeta.h"

/* ------------------------- 内省宏（风格对齐框架 YOMK_CONTEXT_INFO_*） ------------------------- */

/* Loader：机制层内省（已加载库列表 / 单库元信息 / 全量 dump） */
#define YOMK_PLUGIN_LOADER_INFO_LIBS() YOMK_REQUEST("/YomkPluginLoader/libs", nullptr)
#define YOMK_PLUGIN_LOADER_INFO_LIB(libId) \
    YOMK_REQUEST("/YomkPluginLoader/lib", YomkMkPtr(String, libId))
#define YOMK_PLUGIN_LOADER_INFO_ALL() YOMK_REQUEST("/YomkPluginLoader/all", nullptr)

/* Manager：数据层内省（插件列表 / 单插件元信息 / 全量 dump 含实例明细） */
#define YOMK_PLUGIN_MANAGER_INFO_PLUGINS() YOMK_REQUEST("/YomkPluginManager/plugins", nullptr)
#define YOMK_PLUGIN_MANAGER_INFO_PLUGIN(libId) \
    YOMK_REQUEST("/YomkPluginManager/plugin", YomkMkPtr(String, libId))
#define YOMK_PLUGIN_MANAGER_INFO_ALL() YOMK_REQUEST("/YomkPluginManager/all", nullptr)

/* ------------------------- 数据类 ------------------------- */

struct PluginPath
{
    std::string path; /* so 文件路径 */
};

struct PluginMeta
{
    int abi_version = 0;
    std::string name;
    std::string type;
    std::string version;
    std::string author;
    std::string description;
    std::string libPath; /* so 文件路径（Manager 登记时补充） */
};

struct CreateReq
{
    std::string libId;
    std::string instanceName; /* 调用方指定的实例名，同一插件内唯一 */
    std::string instanceFile; /* 透传参数：允许为空，插件系统不读不解析 */
};

struct DestroyReq
{
    std::string libId;
    std::string instanceName;
};

struct BuildReq
{
    std::string workflowPath; /* my_plugin_system.yomk 清单文件路径 */
};

struct InstanceInfo
{
    std::string libId;
    std::string instanceId;   /* 业务 id，默认等于 instanceName，系统不解析 */
    std::string instanceName; /* 系统唯一主键（同一插件内唯一） */
    std::string instanceType;
};

// clang-format off
/* 定义完所有数据类后统一注册 YomkMsg（数组类直接以 std::vector 为 DataType，同框架内置 StringArray 风格） */
YomkMsg(PluginPath, PluginPath, d)
YomkMsg(PluginMeta, PluginMeta, d)
YomkMsg(CreateReq, CreateReq, d)
YomkMsg(DestroyReq, DestroyReq, d)
YomkMsg(BuildReq, BuildReq, d)
YomkMsg(InstanceInfo, InstanceInfo, d)
YomkMsg(std::vector<PluginMeta>, PluginMetaArray, d)
YomkMsg(std::vector<InstanceInfo>, InstanceInfoArray, d)

/* shared_ptr 经消息包在进程内直接持有传递（无序列化，仅限同进程内请求，不可跨进程） */
YomkMsg(std::shared_ptr<YomkPluginInterface>, PluginInstance, d)