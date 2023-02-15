#include <string>
#include "package.hpp"
#include "utils/wrapper.hpp"
#include <dirent.h>
// #include <string.h>
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

/* <Helper functions> */
int countLines(FILE *f) {
    int count = 0;
    Wrap<char *> content(1024);
    while (fgets(content, 1024, f)) {
        count++;
    }
    return count;
}

int countFiles(DIR *dir) {
    int count = 0;
    struct dirent *files;
    while ((files = readdir(dir))) {
        count++;
    }
    return count;
}

int countLinesCmd(const char *cmd) {
    FILE *f;
    if ((f = popen(cmd, "r"))) {
        int count = countLines(f);
        if (!pclose(f)) return count;
    }
    return 0;
}

// macOS < 10.15 does not implement std::filesystem
namespace fs {
    bool exists(const char* filename) {
        FWrap f(filename, "r");
        return f.f;
    }
}
/* </Helper functions> */

void PackageModule::fetch() {
    std::map<std::string, int> packageMap;
    
    if (fs::exists("/usr/bin/pacman")) {
       DWrap pacman("/var/lib/pacman/local");
       int pacmanPkgs = countFiles(pacman) - 3;
       if (pacmanPkgs != 0) {
           packageMap.insert(pkg_pair("pacman", pacmanPkgs));
       }
    } else if (int count = countLinesCmd("pacman -Q 2> /dev/null")) {
        packageMap.insert(pkg_pair("pacman", count));
    }

    if (int count = countLinesCmd("rpm -qa 2> /dev/null")) {
        packageMap.insert(pkg_pair("rpm", count));
    }

    #ifdef __linux__
    if(fs::exists("/usr/bin/flatpak")) {
       DWrap fpApp("/var/lib/flatpak/app");
       int fpPkgs = countFiles(fpApp) - 4; 
       DWrap fpRuntime("/var/lib/flatpak/runtime");
       fpPkgs += countFiles(fpRuntime);
       if (fpPkgs != 0) {
           packageMap.insert(std::pair<std::string, int>("flatpak", fpPkgs));
       }
    } else if (int count = countLinesCmd("flatpak list 2> /dev/null")) {
        packageMap.insert(pkg_pair("flatpak", count - 1));
    }
    #endif

    #ifdef __linux__
    if (int count = countLinesCmd("apk info 2> /dev/null")) {
        packageMap.insert(pkg_pair("apk", count));
    }
    #endif

    if (fs::exists(HOMEBREW_BINARY)) {
       DWrap brew(HOMEBREW_CELLAR);
       int brewPkgs = countFiles(brew) - 3;
       if (brewPkgs != 0) {
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
