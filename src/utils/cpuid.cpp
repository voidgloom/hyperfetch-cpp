#include "cpuid.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

CpuInfo::CpuInfo() {
    FILE *f = fopen("/proc/cpuinfo", "r");

    char *currentLine = new char[128000];
    char *token;

    while (fgets(currentLine, 128000, f) != NULL) {
        // key
        token = strtok(currentLine, ":");
        std::string key = token;
        rtrim(key);
        // value
        token = strtok(NULL, ":");
        std::string value;
        if (token != NULL)
            value = token;
        else
            value = "";
        ltrim(value);
        rtrim(value);
        if (!key.empty())
            map.insert(std::pair<std::string, std::string>(key, value));
    }
    delete[] currentLine;
}

std::string CpuInfo::getValue(std::string key)  {
    return map[key];
}
