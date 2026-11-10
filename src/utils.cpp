#include "utils.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace Utils
{
    std::string openAndReadFile(const char* path)
    {
        std::fstream file(path);

        if (!file.is_open())
        {
            std::cerr << "Failed to open file" << "\n";
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }
}