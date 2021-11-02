#include "package.hpp"
#include <dirent.h>
#include <unistd.h>
#include <map>

void PackageModule::fetch() {
    std::map<std::string, int> packageMap;
    FILE *f;
    if((f = fopen("/usr/bin/pacman", "r"))) {
       fclose(f);
       struct dirent *files;
       int pacmanPkgs = 0;
       DIR *pacman = opendir("/var/lib/pacman/local");
       while ((files = readdir(pacman)) != NULL) {
           pacmanPkgs++;
       }
       if (pacmanPkgs != 0) {
           pacmanPkgs -= 3;
           packageMap.insert(std::pair<std::string,int>("pacman", pacmanPkgs));
       }
    }
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
