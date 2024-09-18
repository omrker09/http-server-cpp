#include "router.h"

void Router::Use(const std::string &path, std::function<void(const std::string &)> callback, httplib::Server server)
{
    this->privatePath = path;
    callback(this->privatePath, server);
};