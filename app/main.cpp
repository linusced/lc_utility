#include "config.hpp"
#include "lc_utility/lc_utility.hpp"

int main(int argc, char const *argv[])
{
    std::cout << PROJECT_NAME << " v." << PROJECT_VERSION << '\n';

    lc_utility::FilePath assets = lc_utility::getAssetsFilePath();

    lc_utility::KeyValueFileRead fileIn{assets + "/test.txt"};
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

    lc_utility::FilePath f = assets + "/test";
    f += "kebab_" + std::to_string(69) + "_yes";
    f += "tjena.dat";

    std::cout << f << '\n';

    auto f2 = assets;
    f2 += "../../test/vadim/kebab.txt";
    std::cout << f2 << '\n';
    f2 += "../fisk.txt";
    std::cout << f2 << '\n';
    return 0;
}