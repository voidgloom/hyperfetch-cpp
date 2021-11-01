#include "osrelease.hpp"
#include <cstring>

OSReleaseParser::OSReleaseParser() {
    FILE *f = fopen("/etc/os-release", "r");
    fseek(f, 0, SEEK_END);
    size_t f_size = ftell(f);

    char *currentLine = new char[f_size];
    char *token;


    rewind(f);
    while (fgets(currentLine, f_size, f) != NULL) {
        token = strtok(currentLine, "=");
        std::string key = token;
        token = strtok(currentLine, "=");
        std::string value = token;
        map.insert(std::pair<std::string, std::string>(key, value));
    }
}

std::string OSReleaseParser::getValue(std::string key)  {
    return map[key];
}
