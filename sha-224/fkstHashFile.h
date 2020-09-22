#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "sha_224.h"

class FkstHashFile
{
public:
    static std::string sha224(const std::string& filePath)
    {
        std::ifstream ifs(filePath);
        const std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));
        ifs.close();
        if (ifs.fail())
        {
            throw std::runtime_error("Failed to open file: " + filePath + "\n");
        }

        std::cout << "File '" << filePath << "' contents:\n" << content << '\n';
        return sha::sha_224(content);
    }
};