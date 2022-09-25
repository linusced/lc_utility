#pragma once

#include "common.hpp"

namespace lc_utility
{
    class FilePath
    {
    public:
        FilePath(const FilePath &fp);
        FilePath(const std::string &str);
        FilePath(const char *c_str);

        operator const std::string &() const { return str; }
        friend std::ostream &operator<<(std::ostream &os, const FilePath &fp);

        friend FilePath operator+(const FilePath &fp, const std::string &str);
        void operator+=(const std::string &str);

    private:
        std::string str;

        void addStr(const std::string &str);
    };
}