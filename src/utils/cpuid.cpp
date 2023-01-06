#include "cpuid.hpp"
#include "trim.hpp"
#include <cstring>

CpuInfo::CpuInfo(bool partial) {
    #ifdef __linux__
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
            ralsei::rtrim(key);
            // value
            token = strtok(NULL, ":");
            std::string value;
            if (token != NULL)
                value = token;
            else
                value = "";
            ralsei::ltrim(value);
            ralsei::rtrim(value);
            if (!key.empty())
                map.insert(std::pair<std::string, std::string>(key, value));
        }
        delete[] currentLine;
    }
    #endif
}

std::string CpuInfo::getValue(std::string key)  {
    #ifdef __linux__
    if (isPartial) {
        FILE *f = fopen("/proc/cpuinfo", "r");

        char *currentLine = new char[256000];
        char *token;

        while (fgets(currentLine, 256000, f) != NULL) {
            // key
            token = strtok(currentLine, ":");
            std::string getKey = token;
            ralsei::rtrim(getKey);
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
            ralsei::ltrim(value);
            ralsei::rtrim(value);
            if (!getKey.empty() && map.count(getKey) == 0 )
                map.insert(std::pair<std::string, std::string>(getKey, value));
            else {
             delete[] currentLine;
             return value;
            }
            delete[] currentLine;
            return value;
        }
        if (map.find(key) != map.end())
            return map[key];
        else
            return "";
    } else {
        if (map.find(key) != map.end())
            return map[key];
        else
            return "";
    }
    #else 
    return "";
    #endif
}
