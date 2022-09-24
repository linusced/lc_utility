#pragma once

#include "bytes_arr.hpp"

namespace lc_utility
{
    class BinaryFileRead : public BytesArrRead
    {
    public:
        BinaryFileRead(const std::string &filePath);
    };

    class BinaryFileWrite : public BytesArrWrite
    {
    public:
        BinaryFileWrite(const std::string &filePath) : filePath(filePath) {}
        ~BinaryFileWrite();

    private:
        std::string filePath;
    };
}