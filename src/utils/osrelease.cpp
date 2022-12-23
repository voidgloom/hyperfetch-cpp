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
    if (std::filesystem::exists("/bedrock/etc/os-release")) {
       f = fopen("/bedrock/etc/os-release", "r");
    }
    else {
       f = fopen("/etc/os-release", "r");
    }
    fseek(f, 0, SEEK_END);
    size_t f_size = ftell(f);

    char *currentLine = new char[f_size];
    char *token;

    rewind(f);
    while (fgets(currentLine, f_size, f) != NULL) {
        // key
        token = strtok(currentLine, "=");
        std::string key = token;
        // value
        token = strtok(NULL, "=");
        // remove quotes and newline from value
        std::string setToValue = "";
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
                    setToValue += token[i];
            }
            i++;
        }

        std::string value = setToValue;
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
