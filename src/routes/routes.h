#ifndef ROUTES_H
#define ROUTES_H

#include <string>
#include "httplib.h"
#include <functional>

class Routes {
    public:
    Routes();
    void Use(
        const std::string &path,
        httplib::Server &server,
        const std::function<void(const std::string &, httplib::Server &server)> &callback
    );
};

#endif