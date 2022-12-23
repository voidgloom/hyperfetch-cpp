
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <list>
#ifdef __linux__
#include "wmList.hpp"
#endif

void WmModule::fetch() {
    std::list<std::string> processNames;
    #ifdef __linux__
    uid_t currentUserId = geteuid();
    struct dirent *files;
    DIR *dir = opendir("/proc/");
    while((files = readdir(dir)) != NULL) {
        if (files->d_name[0] == '1'
            || files->d_name[0] == '2'
            || files->d_name[0] == '3'
            || files->d_name[0] == '4'
            || files->d_name[0] == '5'
            || files->d_name[0] == '6'
            || files->d_name[0] == '7'
            || files->d_name[0] == '8'
            || files->d_name[0] == '9') {
            std::string commFilename = "/proc/";
            commFilename += files->d_name;
            commFilename += "/comm";
            struct stat sFile;
            stat(commFilename.c_str(), &sFile);
            if (sFile.st_uid == currentUserId) {
                std::string exeFilename = "/proc/";
                exeFilename += files->d_name;
                exeFilename += "/exe";
                char *buffer = new char[4096];
                readlink(exeFilename.c_str(), buffer, 4096);
                // does the same thing as basename just in cpp
                // that means oldToken is the name of the executable
                char *token = strtok(buffer, "/");
                std::string oldToken;
                while (token != NULL) {
                    oldToken = token;
                    token = strtok(NULL, "/");
                }
                processNames.push_back(oldToken);
                delete[] buffer;
            }
        }
    }
    for (std::string s : processNames) {
        if (wmList.count(s)) {
            content = wmList.find(s)->second;
            break;
        }
    }
    if (content.empty()) {
        content = "unknown";
    }
    #else
    content = "unknown";
    #endif
    prefix = "WM";

}
