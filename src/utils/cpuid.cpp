#include "cpuid.hpp"
#include "trim.hpp"
#include "wrapper.hpp"
#include <cstring>

CpuInfo::CpuInfo(bool partial) {
    #ifdef __linux__
    if (partial) {
        isPartial = true;
    } else {
        FWrap f("/proc/cpuinfo", "r");

        Wrap<char *> currentLine(1024);
        char *token;

        while (fgets(currentLine, 1024, f) != NULL) {
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
    }
    #endif
}

std::string CpuInfo::getValue(std::string key)  {
    #ifdef __linux__
    if (isPartial) {
        FWrap f("/proc/cpuinfo", "r");

        Wrap<char *> currentLine(1024);
        char *token;

        while (fgets(currentLine, 1024, f) != NULL) {
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
             return value;
            }
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
