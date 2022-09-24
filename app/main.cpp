#include "config.hpp"
#include "lc_utility/lc_utility.hpp"

int main(int argc, char const *argv[])
{
    std::cout << PROJECT_NAME << " v." << PROJECT_VERSION << '\n';

    std::string assets = lc_utility::getAssetsFilePath();
    lc_utility::KeyValueFileRead fileIn{assets + "test.txt"};
    if (fileIn.size() != 0)
    {
        for (auto &pair : fileIn)
        {
            std::string str;
            pair.second.get(str);
            std::cout << pair.first << " = " << str << '\n';
        }
    }

    lc_utility::KeyValueFileWrite fileOut{assets + "test.txt"};
    fileOut.push_back("test", std::string("hello"));
    fileOut.push_back("ALLAHU_AKBAR", std::string("YES INDEED"));
    return 0;
}