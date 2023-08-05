#include "osrelease.hpp"
#include "wrapper.hpp"
#include "utils.hpp"
#include <cstring>
#include <filesystem>
#include <iostream>

std::map<std::string, std::string> OSReleaseParser::map;

OSReleaseParser::OSReleaseParser() {
    #ifdef __linux__
    if (!map.empty()) {
        return;
    }
    FWrap f("/bedrock/etc/os-release", "r");
    if (!f.f)
       f.f = fopen("/etc/os-release", "r");


    auto file_size = file::get_file_size(f);
    Wrap<char *> currentLine(file_size);
    char *token;

    while (fgets(currentLine, file_size, f) != NULL) {
        // key
        token = strtok(currentLine, "=");
        std::string key = token;
        // value
        token = strtok(NULL, "=");
        // remove quotes and newline from value
        Wrap<char *> buf(128);
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
                    buf.o[i - offset] = token[i];
            }
            i++;
        }
        buf.o[i - offset - 1] = '\0';

        std::string value = buf.o;
        map.insert(std::pair<std::string, std::string>(key, value));
    }
    #endif
}

std::string OSReleaseParser::getValue(std::string key)  {
    #ifdef __linux__
    return map[key];
    #else
    return "";
    #endif
}
