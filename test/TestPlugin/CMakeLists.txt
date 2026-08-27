# 示例插件：SHARED 库，编译期引用本扩展安装的 ABI 头文件
# 不安装到 bin（插件由测试程序 dlopen 按路径加载），安装到 lib/plugins 供安装态测试查找
add_library(TestPlugin SHARED
    TestPlugin.cpp
)
target_link_libraries(TestPlugin PRIVATE YomkServer::YomkServer)

install(TARGETS TestPlugin
    LIBRARY DESTINATION lib/plugins
)
