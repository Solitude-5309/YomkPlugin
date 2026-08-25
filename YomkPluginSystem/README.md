# YomkPluginSystem 扩展

基于 [YomkServer](https://github.com/Solitude-5309/YomkServer) 框架的扩展服务。

## 功能

| URL | 功能 | 说明 |
|-----|------|------|
| `/XxxService/version` | 版本查询 | 返回扩展版本信息 |

## 前置条件

- C++17 编译器
- CMake >= 3.14
- YomkServer 已安装（通过 `build_ubuntu.sh` 安装后会自动配置环境变量 `YOMK_PREFIX_PATH` 指向安装路径）

## 编译

```bash
source build_ubuntu.sh
```

> 交互式编译：依次询问 YomkServer 安装路径（前置路径）与扩展安装路径，默认均取 `$YOMK_PREFIX_PATH`，可修改。扩展库与 YomkServer 安装到一起（头文件由 `YomkServer::YomkServer` 的 INTERFACE include 统一提供）。测试程序随扩展安装到 `<安装路径>/bin`，安装后可直接运行 `TestYomkPluginSystem` 验证。

## 工程结构

```
YomkPluginSystem/
├── include/
│   └── XxxService.h        # 服务头文件（类声明）
├── src/
│   └── XxxService.cpp      # 服务实现
├── CMakeLists.txt          # CMake 构建配置
├── build_ubuntu.sh         # 一键编译脚本（交互式）
└── README.md
```

## 使用示例

将以下完整程序拷贝为 main.cpp，安装扩展后可直接编译运行：

```cpp
#include <YomkServer/YomkAPI.h>
#include <YomkPluginSystem/XxxService.h>
#include <iostream>

using namespace yomk;

int main(int argc, char *argv[])
{
    YOMK_INIT();

    // 注册 XxxService（扩展服务需先注册才能使用）
    YOMK_NEW_SERVICE(XxxService);

    // 版本查询请求
    YomkResponse resp = YOMK_REQUEST("/XxxService/version", nullptr);
    if (resp.m_status == YomkResponse::eOk)
    {
        YomkUnPackPkg(resp.m_data, String, version);
        std::cout << "version: " << version->d << std::endl; // 输出: YomkPluginSystem v0.0.1 (WIP)
    }

    return 0;
}
```
