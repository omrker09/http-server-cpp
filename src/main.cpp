#include "nlohmann/json.hpp"
#include <iostream>
#include "httplib.h"
#include "services/files.config.h"
#include "routes/routes.h"
#include "controllers/headers/root.h"
#include "controllers/headers/upload.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

int main(void)
{
  // HTTP server
  int port = 8080;
  httplib::Server server;
  Routes routes;

  routes.Use("/", server, [](const std::string &path, httplib::Server &server) {
    Root::GetRoot(path, server);  // Use the path passed to the lambda
  });

  routes.Use("/upload", server, [](const std::string &path, httplib::Server &server) {
    Upload::PostUpload(path, server);
  });

  server.Post("/post", [](const httplib::Request &req, httplib::Response &res)
              {
    json parsedBody = json::parse(req.body);

    std::string name = parsedBody.value("name", "any");
    int age = parsedBody.value("age", 0);

    if (name.empty() || age <= 0) {
      json errorResponse = {
      {"message", "you did not provide required fields."},
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
    res.set_content(response.dump(), "application/json"); });


  std::cout << "Server is running on http://localhost:" << port << std::endl;
  server.listen("0.0.0.0", port);
}
