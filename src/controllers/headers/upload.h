#ifndef UPLOAD_H
#define UPLOAD_H

#include <string>
#include "httplib.h"

class Upload {
    public:
    static void PostUpload(const std::string &path,httplib::Server &server);
};

#endif