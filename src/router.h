#ifndef ROUTER_H
#define ROUTER_H

#include "httplib.h"
#include <string>
#include <functional> // Use std::function for more flexibility

class Router {
public:
    // Method to register a route with a callback
    void Use(const std::string &path, std::function<void(const std::string &)> callback, httplib::Server server);

private:
    std::string privatePath; // Member variable to store the path
};

#endif
