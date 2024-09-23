#include "headers/root.h"

void Root::GetRoot(const std::string &path, httplib::Server &serverI) {
    serverI.Get(path, [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });
}