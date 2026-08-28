#pragma once
#include "YomkPluginMsgs.h"

#include <mutex>
#include <string>
#include <vector>

using namespace yomk;

/*
 * YomkPluginSystemBuilder：插件系统构建编排层
 * 解析 .yomk 清单（模块目录名@实例名@实例文件，# 为注释），纯请求调用 Manager
 * 完成插件加载与实例创建（实例文件路径作为 instanceFile 透传），自身不持有插件/实例。
 */
class YomkPluginSystemBuilder : public YomkService
{
public:
    YomkPluginSystemBuilder(YomkServer *server);
    virtual ~YomkPluginSystemBuilder() {}
    virtual int init() override;

private:
    /* 清单条目：模块目录名@实例名@实例文件 */
    struct ManifestEntry
    {
        int lineNo = 0;
        std::string moduleDir;    /* 模块目录名（动态库为 <模块目录>/lib/lib<模块目录名>.so） */
        std::string instanceName; /* 实例名（同一插件内唯一） */
        std::string instanceFile; /* 实例文件（位于 <模块目录>/instances/ 下） */
    };

    /* 请求接口 */
    YomkResponse build(YomkPkgPtr pkg);   /* BuildReq -> String 构建结果汇总 */
    YomkResponse version(YomkPkgPtr pkg); /* -> String */
    /* 内省接口 */
    YomkResponse infoAll(YomkPkgPtr pkg); /* -> String 最近一次构建的清单解析结果与状态 */

    /* 清单解析：# 注释忽略（整行/行内），按 @ 切分校验三段 */
    YomkResponse parseManifest(const std::string &workflowPath, std::string &workflowDir,
                               std::vector<ManifestEntry> &entries);

    /* 记录最近一次构建状态（内省用） */
    void recordBuild(const std::string &manifest, const std::string &result,
                     const std::vector<std::string> &entryLines);

    std::mutex m_mutex;
    std::string m_lastManifest;             /* 最近一次构建的清单路径 */
    std::string m_lastResult;               /* 最近一次构建结果（成功汇总 / 失败原因） */
    std::vector<std::string> m_lastEntries; /* 成功条目的解析明细 */
};
