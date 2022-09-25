#include "lc_utility/file_path.hpp"

lc_utility::FilePath::FilePath(const FilePath &fp)
    : str(fp.str) {}

lc_utility::FilePath::FilePath(const std::string &str)
{
    addStr(str);
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
    if (!this->str.empty() && str.front() != '/')
        this->str += '/';

    this->str += str;

    if (this->str.back() != '/')
        this->str += '/';

    size_t prevSlashIndex = this->str.find('/', 0) + 1,
           slashIndex = this->str.find('/', prevSlashIndex) + 1,
           nextSlashIndex = this->str.find('/', slashIndex);

    while (nextSlashIndex != std::string::npos)
    {
        auto dir = this->str.substr(slashIndex, nextSlashIndex - slashIndex);
        if (dir == "..")
        {
            this->str = this->str.substr(0, prevSlashIndex) + this->str.substr(nextSlashIndex + 1);
            slashIndex = this->str.find('/', 0) + 1;
        }

        prevSlashIndex = slashIndex;
        slashIndex = this->str.find('/', slashIndex) + 1;
        nextSlashIndex = this->str.find('/', slashIndex);
    }

    this->str.resize(this->str.size() - 1);
}