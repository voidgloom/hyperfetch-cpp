#include "cpuid.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

CpuInfo::CpuInfo(bool partial) {
    if (partial) {
        isPartial = true;
    } else {
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
}

std::string CpuInfo::getValue(std::string key)  {
    if (isPartial) {
        FILE *f = fopen("/proc/cpuinfo", "r");

        char *currentLine = new char[256000];
        char *token;

        while (fgets(currentLine, 256000, f) != NULL) {
            // key
            token = strtok(currentLine, ":");
            std::string getKey = token;
            rtrim(getKey);
            if (key != getKey) {
                continue;
            }
            // value
            token = strtok(NULL, ":");
            std::string value;
            if (token != NULL)
                value = token;
            else
                value = "";
            ltrim(value);
            rtrim(value);
            if (!getKey.empty() && map.count(getKey) == 0 )
                map.insert(std::pair<std::string, std::string>(getKey, value));
            else {
             delete[] currentLine;
             return value;
            }
            delete[] currentLine;
            return value;
        }
        return map[key];
    } else {
        return map[key];
    }
}
