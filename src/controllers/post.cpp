#include "headers/post.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

void Post::GetPost(const std::string &path,httplib::Server &server) {
    
    server.Post(path, [](const httplib::Request &req, httplib::Response &res) {
    json parsedBody = json::parse(req.body);

    std::string name = parsedBody.value("name", "any");
    int age = parsedBody.value("age", 0);
        json config = json(
        {
        {"name", "omar"},
        {"age", 20}
        }
    );

    if (name.empty() || age <= 0) {
        json errorResponse = {
        {"message", "you did not provide required fields."},
    };
    res.status = 201;
    res.set_content(config.dump(), "application/json");
        return;
    };

    json response = {
        {"name is : ", name},
        {"age is : ", age}
    };

    res.status = 200;
    res.set_content(config.dump(), "application/json"); 
    });
}