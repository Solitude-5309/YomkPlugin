cmake_minimum_required(VERSION 3.14)
project(TestYomkPluginSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(YomkServer REQUIRED)
find_package(YomkPluginSystem REQUIRED)

message(STATUS "YomkPluginSystem version: ${YomkPluginSystem_VERSION}")
message(STATUS "YomkPluginSystem include dirs: ${YomkPluginSystem_INCLUDE_DIRS}")
message(STATUS "YomkPluginSystem lib dir: ${YomkPluginSystem_LIB_DIR}")
message(STATUS "YomkPluginSystem libraries: ${YomkPluginSystem_LIBRARIES}")

add_executable(TestYomkPluginSystem TestYomkPluginSystem.cpp)
target_link_libraries(TestYomkPluginSystem PRIVATE YomkPluginSystem::YomkPluginSystem YomkServer::YomkServer)

# 测试程序随扩展一并安装到 <安装路径>/bin，供用户在任意终端直接运行验证
# 测试程序可能有多个，此处显式列出全部测试目标名（不能用 ${PROJECT_NAME} 占位）
install(TARGETS
    TestYomkPluginSystem
    RUNTIME DESTINATION bin
)
