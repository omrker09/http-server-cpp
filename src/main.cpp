#include "nlohmann/json.hpp"
#include <iostream>
#include "httplib.h"
#include "services/files.config.h"
#include "routes/routes.h"
#include "controllers/headers/root.h"
#include "controllers/headers/upload.h"
#include "controllers/headers/post.h"

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

  routes.Use("/post", server, [](const std::string &path, httplib::Server &server) {
    Post::GetPost(path, server);
  });

  std::cout << "Server is running on http://localhost:" << port << std::endl;
  server.listen("0.0.0.0", port);
}
