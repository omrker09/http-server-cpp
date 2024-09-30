#ifndef POST_H
#define POST_H

#include <string>
#include "httplib.h"

class Post {
    public:
    static void GetPost(const std::string &path,httplib::Server &server);
};

#endif