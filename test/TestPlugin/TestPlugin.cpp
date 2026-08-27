/*
 * TestPlugin：插件系统示例插件
 * 演示完整 ABI 契约：meta 常量导出 + 实例工厂 + 实例删除。
 * 实例命名规则：config_file 非空时直接用作实例名（演示透传参数用法），
 * 否则按计数后缀自动生成（TestInstance-1/2/...），保证同插件内唯一。
 */
#include <YomkPluginSystem/YomkPlugin.h>

#include <atomic>
#include <string>

class MyInstance : public YomkPluginInterface
{
public:
    MyInstance(const std::string &name) : m_name(name) {}
    virtual ~MyInstance() {}

    virtual const char *instanceName() const override { return m_name.c_str(); }
    virtual const char *instanceType() const override { return "demo"; }
    /* instanceId 不覆写，默认等于 instanceName */

private:
    std::string m_name;
};

static const YomkPluginMeta g_meta = {
    YOMK_PLUGIN_ABI_VERSION,
    "TestPlugin",
    "demo",
    "0.0.1",
    "Yomk",
    "Sample plugin for YomkPluginSystem testing"};

static std::atomic<int> g_seq(0);

static const YomkPluginMeta *metaFn()
{
    return &g_meta;
}

static YomkPluginInterface *createFn(const char *config_file)
{
    try
    {
        std::string name;
        if (config_file && *config_file)
        {
            name = config_file; /* 透传参数由插件实现自行决定是否使用 */
        }
        else
        {
            name = "TestInstance-" + std::to_string(++g_seq);
        }
        return new MyInstance(name);
    }
    catch (...)
    {
        return nullptr;
    }
}

static void deleteFn(YomkPluginInterface *instance)
{
    delete instance;
}

YOMK_PLUGIN_EXPORT(metaFn, createFn, deleteFn)
