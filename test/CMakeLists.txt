cmake_minimum_required(VERSION 3.14)
project(TestYomkPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(YomkServer REQUIRED)
find_package(YomkPlugin REQUIRED)

message(STATUS "YomkPlugin version: ${YomkPlugin_VERSION}")
message(STATUS "YomkPlugin include dirs: ${YomkPlugin_INCLUDE_DIRS}")
message(STATUS "YomkPlugin lib dir: ${YomkPlugin_LIB_DIR}")
message(STATUS "YomkPlugin libraries: ${YomkPlugin_LIBRARIES}")

add_executable(TestYomkPlugin TestYomkPlugin.cpp)
target_link_libraries(TestYomkPlugin PRIVATE YomkPlugin::YomkPlugin YomkServer::YomkServer)

# 测试程序随扩展一并安装到 <安装路径>/bin，供用户在任意终端直接运行验证
# 测试程序可能有多个，此处显式列出全部测试目标名（不能用 ${PROJECT_NAME} 占位）
install(TARGETS
    TestYomkPlugin
    RUNTIME DESTINATION bin
)
