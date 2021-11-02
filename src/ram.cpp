#include "ram.hpp"
#include "utils/trim.hpp"
#include <cstring>

void RamModule::fetch() {
    FILE *f = fopen("/proc/meminfo", "r");
    char *cacheMemChar = new char[1024];
    int totalMemNum;
    int bufferMem;
    int freeMem;
    int cacheMem;
    int sReclaimable;
    int i = 0;
    while(fgets(cacheMemChar, 1024, f)) {
        if (i == 0) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            totalMemNum = std::atoi(token) / 1024;
        }
        if (i == 1) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            freeMem = std::atoi(token) / 1024;
        }
        if (i == 3) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            bufferMem = std::atoi(token) / 1024;
        }
        if (i == 4) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            cacheMem = std::atoi(token) / 1024;
        }
        if (i == 23) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            sReclaimable = std::atoi(token) / 1024;
        }
        i++;
    }
    // non-cache non-buffer non-reclaimable used memory
    int ncbrcUsedMem = totalMemNum - freeMem - bufferMem - cacheMem - sReclaimable;

    delete[] cacheMemChar;
    content = std::to_string(ncbrcUsedMem) + "M / " + std::to_string(totalMemNum) + "M";
    prefix = "Memory";
}
