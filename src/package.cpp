#include <string>
#include "package.hpp"
#include "utils/wrapper.hpp"
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <map>

#ifdef __aarch64__
    #define HOMEBREW_CELLAR "/opt/homebrew/Cellar"
    #define HOMEBREW_BINARY "/opt/homebrew/bin/brew"
#else
    #define HOMEBREW_BINARY "/usr/local/bin/brew"
    #define HOMEBREW_CELLAR "/usr/local/Cellar"
#endif

#define pkg_pair std::pair<std::string, int>

int countLines(FILE* f) {
    int count = 0;
    Wrap<char *> content(1024);
    while (fgets(content, 1024, f)) {
        count++;
    }
    return count;
}

void PackageModule::fetch() {
    std::map<std::string, int> packageMap;
    FILE *f;

    if((f = fopen("/usr/bin/pacman", "r"))) {
       fclose(f);
       struct dirent *files;
       int pacmanPkgs = -3;
       DWrap pacman("/var/lib/pacman/local");
       while ((files = readdir(pacman)) != NULL) {
           pacmanPkgs++;
       }
       if (pacmanPkgs != 0) {
           packageMap.insert(pkg_pair("pacman", pacmanPkgs));
       }
    } else if((f = popen("pacman -Q 2> /dev/null", "r"))) {
        int count = countLines(f);
        if(!pclose(f)) packageMap.insert(pkg_pair("pacman", count));
    }

    if((f = popen("rpm -qa 2> /dev/null", "r"))) {
        int count = countLines(f);
        if (!pclose(f)) packageMap.insert(pkg_pair("rpm", count));
    }

    #ifdef __linux__
    if((f = fopen("/usr/bin/flatpak", "r"))) {
       fclose(f);
       struct dirent *files;
       int fpPkgs = 0;
       DWrap fpApp("/var/lib/flatpak/app");
       while ((files = readdir(fpApp)) != NULL) {
           fpPkgs++;
       }
       DWrap fpRuntime("/var/lib/flatpak/runtime");
       while ((files = readdir(fpRuntime)) != NULL) {
           fpPkgs++;
       }
       if (fpPkgs != 0) {
           fpPkgs -= 4;
           packageMap.insert(std::pair<std::string, int>("flatpak", fpPkgs));
       }
    } else if((f = popen("flatpak list 2> /dev/null", "r"))) {
        int count = countLines(f);
        if (!pclose(f)) packageMap.insert(pkg_pair("flatpak", count - 1));
    }
    #endif

    #ifdef __linux__
    if((f = popen("apk info 2> /dev/null", "r"))) {
        int count = countLines(f);
        if (!pclose(f)) packageMap.insert(pkg_pair("apk", count));
    }
    #endif

    if((f = fopen(HOMEBREW_BINARY, "r"))) {
       fclose(f);
       struct dirent *files;
       int brewPkgs = 0;
       DWrap brew(HOMEBREW_CELLAR);
       while ((files = readdir(brew)) != NULL) {
           brewPkgs++;
       }
       if (brewPkgs != 0) {
           brewPkgs -= 3;
           packageMap.insert(pkg_pair("homebrew", brewPkgs));
       }
    }

    // iterate over packageMap and it to the modules content
    std::map<std::string, int>::iterator it;
    int elements = 0;
    // loop over packageMap once to count elements
    for (it = packageMap.begin(); it != packageMap.end(); it++) {
        elements++;
    }
    int i = 1;
    for (it = packageMap.begin(); it != packageMap.end(); it++) {
        if (i == elements) {
            content += std::to_string(it->second) + " (" + it->first + ")";
        } else {
            content += std::to_string(it->second) + " (" + it->first + "), ";
        }
        i++;
    }
    if (content.empty())
        content = "0";

    prefix = "Pkgs";
}
