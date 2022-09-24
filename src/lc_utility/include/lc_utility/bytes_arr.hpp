#pragma once

#include "common.hpp"

namespace lc_utility
{
    class BytesArrRead
    {
    public:
        size_t size() const { return bytes.size(); }
        const uint8_t *data() const { return bytes.data(); }
        size_t getReadIndex() const { return readIndex; }
        void setReadIndex(size_t index) { readIndex = index; }
        bool eof() const { return readIndex >= bytes.size(); }

        template <typename T>
        void read(T *data, size_t arrSize)
        {
            if (arrSize == 0)
                return;

            size_t bytesSize = sizeof(T) * arrSize;
            if (readIndex + bytesSize > bytes.size())
                throw std::invalid_argument("lc_utility::BytesArrRead::read End of file reached!");

            std::memcpy(data, bytes.data() + readIndex, bytesSize);
            readIndex += bytesSize;
        }

        template <typename T>
        T read()
        {
            T data;
            read(&data, 1);
            return data;
        }
        template <typename T>
        void read(std::vector<T> &arr)
        {
            read(arr.data(), arr.size());
        }
        void read(std::string &str)
        {
            read(str.data(), str.size());
        }

    protected:
        BytesArrRead() {}

        std::vector<uint8_t> bytes;
        size_t readIndex{0};
    };

    class BytesArrWrite
    {
    public:
        size_t size() const;
        const uint8_t *data() const;

        template <typename T>
        void write(const T *data, size_t arrSize)
        {
            if (arrSize == 0)
                return;

            size_t i = bytes.size(), bytesSize = sizeof(T) * arrSize;
            bytes.resize(i + bytesSize);
            std::memcpy(bytes.data() + i, data, bytesSize);
        }

        template <typename T>
        void write(const T &data)
        {
            write(&data, 1);
        }
        template <typename T>
        void write(const std::vector<T> &arr)
        {
            write(arr.data(), arr.size());
        }
        void write(const std::string &str)
        {
            write(str.data(), str.size());
        }

    protected:
        BytesArrWrite() {}

        std::vector<uint8_t> bytes;
    };
}