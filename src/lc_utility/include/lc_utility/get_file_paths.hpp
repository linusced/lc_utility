#pragma once

#include "common.hpp"

#ifdef __APPLE__
#include <CoreServices/CoreServices.h>
#endif

namespace lc_utility
{
    std::string getAssetsFilePath();
    std::string getApplicationSupportFilePath(const std::string &appName);

    std::map<std::string, std::string> getDefaultFilePaths();
}