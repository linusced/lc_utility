#include "lc_utility/file_path.hpp"

lc_utility::FilePath::FilePath(const FilePath &fp)
    : str(fp.str) {}

lc_utility::FilePath::FilePath(const std::string &str)
    : str(str)
{
    if (this->str.back() == '/')
        this->str.resize(this->str.size() - 1);
}

lc_utility::FilePath::FilePath(const char *c_str)
    : FilePath(std::string(c_str)) {}

std::ostream &lc_utility::operator<<(std::ostream &os, const FilePath &fp)
{
    os << fp.str;
    return os;
}

lc_utility::FilePath lc_utility::operator+(const FilePath &fp, const std::string &str)
{
    lc_utility::FilePath fp_out{fp};
    fp_out.addStr(str);
    return fp_out;
}
void lc_utility::FilePath::operator+=(const std::string &str)
{
    this->addStr(str);
}

void lc_utility::FilePath::addStr(const std::string &str)
{
    if (str.front() != '/')
        this->str += '/';

    this->str += str;

    if (this->str.back() == '/')
        this->str.resize(this->str.size() - 1);
}