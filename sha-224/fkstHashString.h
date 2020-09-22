#pragma once
#include <string>
#include "sha_224.h"

class FkstHashString
{
public:
    static std::string sha224(const std::string& str)
    {
        return sha::sha_224(str);
    }
};