#include "lc_utility/key_value_file.hpp"

size_t lc_utility::KeyValueFile::size() const
{
    return arr.size();
}

std::vector<std::pair<std::string, lc_utility::KeyValueFile::Data>>::iterator lc_utility::KeyValueFile::begin()
{
    return arr.begin();
}
std::vector<std::pair<std::string, lc_utility::KeyValueFile::Data>>::iterator lc_utility::KeyValueFile::end()
{
    return arr.end();
}
std::vector<std::pair<std::string, lc_utility::KeyValueFile::Data>>::iterator lc_utility::KeyValueFile::find(const std::string &key, DataType type)
{
    for (auto it = begin(); it != end(); it++)
        if (it->first == key)
        {
            if (type != DATA_STR && type != it->second.type)
                try
                {
                    if (type == DATA_INT)
                    {
                        size_t end;
                        int64_t i = std::stoll(it->second.str, &end);
                        if (end != it->second.str.size())
                            throw "";

                        it->second.integer = i;
                    }
                    else if (type == DATA_FLOAT)
                    {
                        size_t end;
                        double d = std::stod(it->second.str, &end);
                        if (end != it->second.str.size())
                            throw "";

                        it->second.floating = d;
                    }
                    else if (type == DATA_BOOL)
                        it->second.boolean = it->second.str == "TRUE" || it->second.str == "true";

                    it->second.type = type;
                }
                catch (const std::exception &e)
                {
                    continue;
                }

            return it;
        }

    return end();
}

std::string lc_utility::KeyValueFile::serialize(std::string str)
{
    for (size_t c{0}; c < str.size(); c++)
        if (str[c] == '\n' || str[c] == '\r' || str[c] == '\t' || str[c] == '\0' || str[c] == '"' || str[c] == '\\')
        {
            char insertChar{'n'};

            if (str[c] == '\r')
                insertChar = 'r';
            else if (str[c] == '\t')
                insertChar = 't';
            else if (str[c] == '\0')
                insertChar = '0';
            else if (str[c] == '"')
                insertChar = '"';
            else if (str[c] == '\\')
                insertChar = '\\';

            str[c] = '\\';
            str.insert(str.begin() + c + 1, insertChar);
            c++;
        }

    return str;
}
std::string lc_utility::KeyValueFile::deserialize(std::string str)
{
    for (size_t c{0}; c < str.size() - 1; c++)
        if (str[c] == '\\' &&
            (str[c + 1] == 'n' || str[c + 1] == 'r' || str[c + 1] == 't' || str[c + 1] == '0' || str[c + 1] == '"' || str[c + 1] == '\\'))
        {
            if (str[c + 1] == 'n')
                str[c] = '\n';
            else if (str[c + 1] == 'r')
                str[c] = '\r';
            else if (str[c + 1] == 't')
                str[c] = '\t';
            else if (str[c + 1] == '0')
                str[c] = '\0';
            else if (str[c + 1] == '"')
                str[c] = '"';

            str.erase(str.begin() + c + 1);
        }

    return str;
}

lc_utility::KeyValueFileRead::KeyValueFileRead(const std::string &filePath)
    : KeyValueFile(filePath)
{
    std::ifstream fileIn{filePath, std::ios::binary};
    if (fileIn.is_open())
    {
        std::string str;

        fileIn.seekg(0, std::ios::end);
        str.resize(fileIn.tellg());
        fileIn.seekg(0, std::ios::beg);
        fileIn.read(str.data(), str.size());
        fileIn.close();

        std::string key, input;

        size_t beginIndex{0}, endIndex{0};
        while (true)
        {
            endIndex = beginIndex = str.find('"', endIndex);
            if (beginIndex == std::string::npos)
                break;

            do
            {
                endIndex = str.find('"', endIndex + 1);
            } while (endIndex != std::string::npos && str[endIndex - 1] == '\\');

            if (endIndex == std::string::npos)
                break;

            beginIndex++;
            input = deserialize(str.substr(beginIndex, endIndex - beginIndex));
            endIndex++;

            if (key.empty())
                key = input;
            else
            {
                arr.push_back({key, Data{input}});
                key.clear();

                if (endIndex == str.size() || str[endIndex] != ',')
                    break;
            }
        }
    }
}

lc_utility::KeyValueFileWrite::~KeyValueFileWrite()
{
    std::ofstream fileOut(filePath);
    if (fileOut.is_open())
    {
        size_t i{0};

        for (auto [key, value] : arr)
        {
            if (i != 0)
                fileOut << '\n';

            fileOut << '\"' << serialize(key) << "\": \"";

            switch (value.type)
            {
            case DATA_STR:
                fileOut << serialize(value.str);
                break;
            case DATA_INT:
                fileOut << value.integer;
                break;
            case DATA_FLOAT:
                fileOut << value.floating;
                break;
            case DATA_BOOL:
                fileOut << (value.boolean ? "true" : "false");
                break;
            }
            fileOut << '"';

            if (i != arr.size() - 1)
                fileOut << ',';

            i++;
        }
    }
}

void lc_utility::KeyValueFileWrite::push_back(const std::string &key, const std::string &value)
{
    arr.push_back({key, {value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, int64_t value)
{
    arr.push_back({key, {value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, int32_t value)
{
    arr.push_back({key, {(int64_t)value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, int16_t value)
{
    arr.push_back({key, {(int64_t)value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, int8_t value)
{
    arr.push_back({key, {(int64_t)value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, double value)
{
    arr.push_back({key, {value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, float value)
{
    arr.push_back({key, {(float)value}});
}
void lc_utility::KeyValueFileWrite::push_back(const std::string &key, bool value)
{
    arr.push_back({key, {value}});
}

void lc_utility::KeyValueFileWrite::clear()
{
    arr.clear();
}