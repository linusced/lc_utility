#include "lc_utility/binary_file.hpp"

lc_utility::BinaryFileRead::BinaryFileRead(const std::string &filePath)
{
    std::ifstream fileIn{filePath, std::ios::binary};
    if (fileIn.is_open())
    {
        fileIn.seekg(0, std::ios::end);
        size_t size = fileIn.tellg();
        fileIn.seekg(0, std::ios::beg);

        bytes.resize(size);
        fileIn.read((char *)bytes.data(), size);
    }
}

lc_utility::BinaryFileWrite::~BinaryFileWrite()
{
    std::ofstream fileOut(filePath, std::ios::binary);
    if (fileOut.is_open())
    {
        fileOut.write((const char *)bytes.data(), bytes.size());
    }
}