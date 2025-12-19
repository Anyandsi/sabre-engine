#include "FileReader.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace FileReader
{
    std::string readFile(const std::filesystem::path &path)
    {
        std::ifstream inputStream(path, std::ios::in);
        if (!inputStream.is_open())
        {
            throw std::runtime_error("Failed to open file at " + path.string());
        }

        std::ostringstream outputStream;
        outputStream << inputStream.rdbuf();
        return outputStream.str();
    }
}