#include "headers/upload.h"
#include "services/files.config.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

void Upload::PostUpload(const std::string &path,httplib::Server &server)
{
    server.Post(path, [](const httplib::Request &req, httplib::Response &res) {

    std::string expectedImages[] = {"png", "jpg", "jpeg", "webp", "svg", "gif", "avif"};
    std::string expectedVideos[] = {"mp4", "mov", "avi", "wvm", "avchd", "webm", "flv"};

    if (req.is_multipart_form_data()) {
      // Loop over all files
    for (const auto& file : req.files) {
        const std::string& fileKey = file.first;  // The name of the file field
        const auto& fileContent = file.second;    // Contains the uploaded file's metadata and content
        
        bool isImageFound = false;
        bool isVideoFound = false;

        for (const std::string fName : expectedImages) {
            if (fileContent.filename.find("." + fName) != std::string::npos) {
                isImageFound = true;
                break;
            }
        }

        for (const std::string file : expectedVideos) {
            if (fileContent.filename.find("." + file) != std::string::npos) {
                isVideoFound = true;
                break;
            }
        }
        
        // Save the file based on image type
        if (isImageFound) {
            FilesConfig::saveImages(FilesConfig::generateNewFilename(fileContent.filename), fileContent.content);
        } else if (isVideoFound){
            FilesConfig::saveVideo(FilesConfig::generateNewFilename(fileContent.filename), fileContent.content);
        } else {
            FilesConfig::saveFile(FilesConfig::generateNewFilename(fileContent.filename), fileContent.content);
        }

        // Log success
        std::cout << "File " << fileContent.filename << " uploaded successfully." << std::endl;
    }

    json response = { {"message", "File(s) uploaded successfully!"} };
    res.set_content(response.dump(), "application/json");
    res.status = 200;
    } else {
        json errorResponse = { {"message", "Invalid form data"} };
        res.set_content(errorResponse.dump(), "application/json");
        res.status = 400;
    }
    // finish.
    });
}