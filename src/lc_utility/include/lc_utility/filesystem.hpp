#pragma once

#include "common.hpp"

#ifdef __APPLE__
#include <CoreServices/CoreServices.h>
#endif

#ifdef __unix
#error lc_utility::filesystem is not supported on Linux
#endif

#ifdef _WIN32
#error lc_utility::filesystem is not supported on Windows
#endif

namespace lc_utility
{
    std::string getAssetsFilePath();
    std::string getApplicationSupportFilePath(const std::string &appName);

    std::map<std::string, std::string> getDefaultFilePaths();
}