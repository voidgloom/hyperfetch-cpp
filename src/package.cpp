#include "package.hpp"
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

int countLines(FILE* f) {
    int count = 0;
    char *content = (char *) malloc(1024);
    while (fgets(content, 1024, f)) {
        count++;
    }
    free(content);
    return count;
}

void PackageModule::fetch() {
    std::map<std::string, int> packageMap;
    FILE *f;

    if((f = fopen("/usr/bin/pacman", "r"))) {
       fclose(f);
       struct dirent *files;
       int pacmanPkgs = -3;
       DIR *pacman = opendir("/var/lib/pacman/local");
       while ((files = readdir(pacman)) != NULL) {
           pacmanPkgs++;
       }
       if (pacmanPkgs != 0) {
           packageMap.insert(std::pair<std::string,int>("pacman", pacmanPkgs));
       }
    } else if((f = popen("pacman -Q 2> /dev/null", "r"))) {
        int count = countLines(f);
        if(!pclose(f)) packageMap.insert(std::pair<std::string,int>("pacman", count));
    }

    if((f = popen("rpm -qa 2> /dev/null", "r"))) {
        int count = countLines(f);
        if (!pclose(f)) packageMap.insert(std::pair<std::string,int>("rpm", count));
    }

    #ifdef __linux__
    if((f = fopen("/usr/bin/flatpak", "r"))) {
       fclose(f);
       struct dirent *files;
       int fpPkgs = 0;
       DIR *fpApp = opendir("/var/lib/flatpak/app");
       while ((files = readdir(fpApp)) != NULL) {
           fpPkgs++;
       }
       DIR *fpRuntime = opendir("/var/lib/flatpak/runtime");
       while ((files = readdir(fpRuntime)) != NULL) {
           fpPkgs++;
       }
       if (fpPkgs != 0) {
           fpPkgs -= 4;
           packageMap.insert(std::pair<std::string,int>("flatpak", fpPkgs));
       }
    } else if((f = popen("flatpak list 2> /dev/null", "r"))) {
        int count = countLines(f);
        if (!pclose(f)) packageMap.insert(std::pair<std::string,int>("flatpak", count - 1));
    }
    #endif

    #ifdef __linux__
    if((f = popen("apk info 2> /dev/null", "r"))) {
        int count = countLines(f);
        if (!pclose(f)) packageMap.insert(std::pair<std::string,int>("apk", count));
    }
    #endif

    if((f = fopen(HOMEBREW_BINARY, "r"))) {
       fclose(f);
       struct dirent *files;
       int brewPkgs = 0;
       DIR *brew = opendir(HOMEBREW_CELLAR);
       while ((files = readdir(brew)) != NULL) {
           brewPkgs++;
       }
       if (brewPkgs != 0) {
           brewPkgs -= 3;
           packageMap.insert(std::pair<std::string,int>("homebrew", brewPkgs));
       }
       closedir(brew);
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
