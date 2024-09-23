#include "routes.h"

Routes::Routes() {};

void Routes::Use
(
    const std::string &path,
    httplib::Server &server,
    const std::function<void(const std::string &, httplib::Server &server)> &callback
) {
    callback(path, server);  // Call the callback, passing the path and the existing server instance
}
