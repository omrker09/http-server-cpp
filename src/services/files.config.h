#ifndef FILES_CONFIG_H
#define FILES_CONFIG_H
#include <string>     // For std::string
#include <ctime>      // For std::time
#include <sstream>    // For std::stringstream
#include <direct.h>   // For creating windows directories
#include <fstream>    // For saving files
#include <sys/stat.h> // For checking if directory exists

class FilesConfig {
    public:
    // this method will extract the original filename and rename it with timestamp to prevent files collision.
    static std::string generateNewFilename(const std::string &originalFilename);

    // saving images files
    static void saveImages(const std::string &fileName, const std::string &content);

    // saving videos
    static void saveVideo(const std::string &fileName, const std::string &content);

    // saving any file
    static void saveFile(const std::string &filename, const std::string &content);

    // Verify if directory already exist to prevent re-create it.
    static bool directoryExists(const std::string &path);

    // create a directory
    static void createDirectory(const std::string &path);
};

#endif