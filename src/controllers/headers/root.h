#ifndef ROOT_H
#define ROOT_H

#include <string>
#include "httplib.h"

class Root {
   // private:
   // std::string &path;

    public:
    static void GetRoot(const std::string &path,httplib::Server &server);
};

#endif