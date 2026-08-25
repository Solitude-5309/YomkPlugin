#pragma once
#include <YomkServer/YomkAPI.h>

using namespace yomk;

class XxxService : public YomkService
{
public:
    XxxService(YomkServer *server);
    virtual ~XxxService() {}
    virtual int init() override;

private:
    YomkResponse version(YomkPkgPtr pkg);
};
