#include "files.config.h"

std::string FilesConfig::generateNewFilename(const std::string &originalFilename)
{
    // Find the position of the last '.' to extract the file extension
    size_t dotPos = originalFilename.find_last_of(".");

    std::string extension = (dotPos != std::string::npos) ? originalFilename.substr(dotPos) : "";
    std::string baseName = (dotPos != std::string::npos) ? originalFilename.substr(0, dotPos) : originalFilename;

    std::time_t currentTime = std::time(nullptr);
    std::stringstream newFilename;
    newFilename << baseName << "_" << currentTime << extension;

    return newFilename.str();
}

void FilesConfig::createDirectory(const std::string &path)
{
    _mkdir(path.c_str()); // Create directory on Windows
}

// Verify if directory already exist to prevent re-create it.
bool FilesConfig::directoryExists(const std::string &path)
{
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
    {
        return false; // Directory does not exist
    }
    return (info.st_mode & S_IFDIR) != 0;
}

// saving images files
void FilesConfig::saveImages(const std::string &fileName, const std::string &content)
{
    std::string dirName = "uploads/images";
    if (!FilesConfig::directoryExists(dirName))
    {
        FilesConfig::createDirectory(dirName);
    }
    std::ofstream file(dirName + "/" + fileName, std::ios::binary);
    file.write(content.c_str(), content.size());
    file.close();
}

void FilesConfig::saveVideo(const std::string &fileName, const std::string &content)
{
    std::string dirName = "uploads/vidoes";

    if (!FilesConfig::directoryExists(dirName)) {
        FilesConfig::createDirectory(dirName);
    }
    std::ofstream file(dirName + "/" + fileName, std::ios::binary);
    file.write(content.c_str(), content.size());
    file.close();
}

// saving any file
void FilesConfig::saveFile(const std::string &filename, const std::string &content)
{
    std::string uploadDir = "uploads/files";
    if (!FilesConfig::directoryExists(uploadDir))
    {
        FilesConfig::createDirectory(uploadDir);
    }
    std::ofstream outFile(uploadDir + "/" + filename, std::ios::binary);
    outFile.write(content.c_str(), content.size());
    outFile.close();
}

