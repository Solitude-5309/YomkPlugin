#include "XxxService.h"

XxxService::XxxService(YomkServer *server)
    : YomkService(server)
{
    name("/XxxService");
}

int XxxService::init()
{
    YomkInstallFunc("/version", XxxService::version);
    YOMK_INFO_TAG("XxxService::init", "install func [ /version ] to", name());
    return 0;
}

YomkResponse XxxService::version(YomkPkgPtr pkg)
{
    std::string version = "YomkPlugin v" EXTENSION_VERSION " (WIP)";
    return YomkResponse(YomkResponse::eOk, "ok", YomkMkPtr(String, version));
}
