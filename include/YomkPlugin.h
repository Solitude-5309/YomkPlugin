#pragma once
#include "YomkPluginMeta.h"
#include "YomkPluginInterface.h"

/*
 * 插件导出契约：宿主 dlsym 查找的固定符号名（extern "C"）：
 *   const YomkPluginMeta *yomk_plugin_meta();                         返回静态常量指针
 *   YomkPluginInterface *yomk_plugin_create_instance(const char *config_file);
 *   void yomk_plugin_delete_instance(YomkPluginInterface *instance);  内部 delete
 *
 * config_file 为透传参数（允许传空），插件系统不读不解析，由插件实现自行决定是否使用。
 * 所有导出函数在插件侧 try/catch，异常时 create 返回 nullptr。
 */
#define YOMK_PLUGIN_SYMBOL_META "yomk_plugin_meta"
#define YOMK_PLUGIN_SYMBOL_CREATE_INSTANCE "yomk_plugin_create_instance"
#define YOMK_PLUGIN_SYMBOL_DELETE_INSTANCE "yomk_plugin_delete_instance"

/* 插件导出函数类型 */
typedef const YomkPluginMeta *(*YomkPluginMetaFunc)();
typedef YomkPluginInterface *(*YomkPluginCreateInstanceFunc)(const char *config_file);
typedef void (*YomkPluginDeleteInstanceFunc)(YomkPluginInterface *instance);

/* 插件侧一键导出宏：三个 C 函数即完整契约 */
#define YOMK_PLUGIN_EXPORT(MetaFn, CreateFn, DeleteFn)                                   \
    extern "C" const YomkPluginMeta *yomk_plugin_meta() { return MetaFn(); }             \
    extern "C" YomkPluginInterface *yomk_plugin_create_instance(const char *config_file) \
    {                                                                                    \
        return CreateFn(config_file);                                                    \
    }                                                                                    \
    extern "C" void yomk_plugin_delete_instance(YomkPluginInterface *instance)           \
    {                                                                                    \
        DeleteFn(instance);                                                              \
    }
