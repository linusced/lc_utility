#include "lc_utility/filesystem.hpp"

std::string lc_utility::getAssetsFilePath()
{
    std::string path;

#ifdef __APPLE__
    CFStringRef appBundle_UTI;
    bool isAppBundle = CFURLCopyResourcePropertyForKey(CFBundleCopyBundleURL(CFBundleGetMainBundle()), kCFURLTypeIdentifierKey, &appBundle_UTI, NULL) && appBundle_UTI && UTTypeConformsTo(appBundle_UTI, kUTTypeApplicationBundle);

    if (isAppBundle)
    {
        char chPath[PATH_MAX];
        CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        CFURLGetFileSystemRepresentation(resourcesURL, true, (UInt8 *)chPath, PATH_MAX);
        CFRelease(resourcesURL);
        chdir(chPath);

        path = std::string(chPath) + "/";
    }
    else
    {
        std::string currentPath = std::filesystem::current_path().string();
        size_t substrIndex = currentPath.find("build/");
        if (substrIndex != std::string::npos)
            path = currentPath.substr(0, substrIndex) + "assets/";
        else
            path = "assets/";
    }
#endif

    return path;
}

std::string lc_utility::getApplicationSupportFilePath(const std::string &appName)
{
    std::string path;

#ifdef __APPLE__
    char chPath[PATH_MAX];
    FSRef ref;
    FSFindFolder(kUserDomain, kApplicationSupportFolderType, kCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);

    path = std::string(chPath) + "/" + appName + "/";

    if (!std::filesystem::is_directory(path))
        std::filesystem::create_directory(path);
#endif

    return path;
}

std::map<std::string, std::string> lc_utility::getDefaultFilePaths()
{
    std::map<std::string, std::string> result;

#ifdef __APPLE__
    char chPath[PATH_MAX];
    FSRef ref;

    FSFindFolder(kUserDomain, kDocumentsFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Documents"] = std::string(chPath);

    FSFindFolder(kUserDomain, kDownloadsFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Downloads"] = std::string(chPath);

    FSFindFolder(kUserDomain, kMusicDocumentsFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Music"] = std::string(chPath);

    FSFindFolder(kUserDomain, kPictureDocumentsFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Pictures"] = std::string(chPath);

    FSFindFolder(kUserDomain, kDesktopFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Desktop"] = std::string(chPath);

    FSFindFolder(kUserDomain, kMovieDocumentsFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Movies"] = std::string(chPath);

    FSFindFolder(kUserDomain, kApplicationsFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Applications"] = std::string(chPath);

    FSFindFolder(kUserDomain, kPublicFolderType, kDontCreateFolder, &ref);
    FSRefMakePath(&ref, (UInt8 *)&chPath, PATH_MAX);
    result["Public"] = std::string(chPath);

    result["Root"] = std::filesystem::current_path().root_path().string();
#endif

    return result;
}