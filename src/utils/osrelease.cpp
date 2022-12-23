#include "osrelease.hpp"
#include <cstring>
#include <filesystem>
#include <iostream>

std::map<std::string, std::string> OSReleaseParser::map;

OSReleaseParser::OSReleaseParser() {
    #ifdef __linux__
    if (!map.empty()) {
        return;
    }
    FILE *f;
    if (!(f = fopen("/bedrock/etc/os-release", "r"))) {
       f = fopen("/etc/os-release", "r");
    }

    char *currentLine = new char[4096];
    char *token;

    while (fgets(currentLine, 4096, f) != NULL) {
        // key
        token = strtok(currentLine, "=");
        std::string key = token;
        // value
        token = strtok(NULL, "=");
        // remove quotes and newline from value
        char *buf = new char[128];
        int i = 0;
        int offset = 0;
        while (token[i] != '\0') {
            switch (token[i]) {
                case '\"':
                    offset++;
                    break;
                case '\n':
                    break;
                default:
                    buf[i - offset] = token[i];
            }
            i++;
        }
        buf[i - offset - 1] = '\0';

        std::string value = buf;
        delete[] buf;
        map.insert(std::pair<std::string, std::string>(key, value));
    }
    delete[] currentLine;
    #endif
}

std::string OSReleaseParser::getValue(std::string key)  {
    #ifdef __linux__
    return map[key];
    #else
    return "";
    #endif
}
