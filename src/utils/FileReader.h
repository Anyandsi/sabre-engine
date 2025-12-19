#pragma once

#include <string>
#include <filesystem>

namespace FileReader
{
    /**
     * @brief Reads contents of a file and outputs to a string
     */
    std::string readFile(const std::filesystem::path &path);
}