#include "nlohmann/json.hpp"
#include <iostream>
#include "router.h"

using json = nlohmann::json;

void IndexPath(const std::string &path) {
    httplib::Server server;
    // Define the GET route within the callback
    server.Get(path.c_str(), [](const httplib::Request &req, httplib::Response &res) {
        json jsonArray = json::array({
            { {"name", "John"}, {"age", 30} },
            { {"name", "Jane"}, {"age", 25} },
            { {"name", "Mike"}, {"age", 40} }
        });

        // Set the response to return the first name as JSON
        res.set_content(jsonArray[0]["name"].dump(), "application/json");
    });
}


int main(void)
{
  // HTTP
  int port = 8080;
  httplib::Server server;
  
  Router router;
  router.Use("/", IndexPath, server);
  
  server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });

  server.Post("/post", [](const httplib::Request& req, httplib::Response& res) {
    json parsedBody = json::parse(req.body);

    std::string name = parsedBody.value("name", "any");
    int age = parsedBody.value("age", 0);

    if (name.empty() || age <= 0) {
      json errorResponse = {
      {"message", "you did not provided required fileds."},
    };
      res.status = 401;
      res.set_content(errorResponse.dump(), "application/json");
      return;
    };

    json response = {
      {"name is : ", name},
      {"age is : ", age}
    };
    res.status = 200;
    res.set_content(response.dump(), "application/json");
  });

  std::cout << "server is running on http://localhost:" << port << std::endl;
  server.listen("0.0.0.0", port);
}
