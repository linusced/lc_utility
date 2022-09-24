#pragma once

#include "common.hpp"

namespace lc_utility
{
    class KeyValueFile
    {
    public:
        enum DataType
        {
            DATA_STR,
            DATA_INT,
            DATA_FLOAT,
            DATA_BOOL
        };

        struct Data
        {
        private:
            std::string str;
            int64_t integer;
            double floating;
            bool boolean;

            DataType type;

            Data(std::string value)
            {
                this->type = DATA_STR;
                this->str = value;
            }
            Data(int64_t value)
            {
                this->type = DATA_INT;
                this->integer = value;
            }
            Data(double value)
            {
                this->type = DATA_FLOAT;
                this->floating = value;
            }
            Data(bool value)
            {
                this->type = DATA_BOOL;
                this->boolean = value;
            }

        public:
            DataType getType() const { return type; }

            void get(std::string &out) const { out = str; }
            void get(int64_t &out) const { out = integer; }
            void get(int32_t &out) const { out = integer; }
            void get(int16_t &out) const { out = integer; }
            void get(int8_t &out) const { out = integer; }
            void get(double &out) const { out = floating; }
            void get(float &out) const { out = floating; }
            void get(bool &out) const { out = boolean; }

            friend class KeyValueFile;
            friend class KeyValueFileRead;
            friend class KeyValueFileWrite;
        };

        size_t size() const;

        std::vector<std::pair<std::string, Data>>::iterator begin();
        std::vector<std::pair<std::string, Data>>::iterator end();
        std::vector<std::pair<std::string, Data>>::iterator find(const std::string &key, DataType type);

        friend class KeyValueFileWrite;

    protected:
        KeyValueFile(const std::string &filePath) : filePath(filePath) {}

        std::vector<std::pair<std::string, Data>> arr;
        std::string filePath;

        std::string serialize(std::string str);
        std::string deserialize(std::string str);
    };

    class KeyValueFileRead : public KeyValueFile
    {
    public:
        KeyValueFileRead(const std::string &filePath);
    };

    class KeyValueFileWrite : public KeyValueFile
    {
    public:
        KeyValueFileWrite(const std::string &filePath) : KeyValueFile(filePath) {}
        KeyValueFileWrite(const KeyValueFile &input) : KeyValueFile(input.filePath) { this->arr = input.arr; }
        ~KeyValueFileWrite();

        void push_back(const std::string &key, const std::string &value);
        void push_back(const std::string &key, int64_t value);
        void push_back(const std::string &key, int32_t value);
        void push_back(const std::string &key, int16_t value);
        void push_back(const std::string &key, int8_t value);
        void push_back(const std::string &key, long double value);
        void push_back(const std::string &key, double value);
        void push_back(const std::string &key, float value);
        void push_back(const std::string &key, bool value);

        void clear();
    };
}