#include "utils/trim.hpp"
#include "utils/bar.hpp"
#include "utils/wrapper.hpp"
#include <cstring>
#include <cmath>

void RamModule::fetch(bool bar) {


    prefix = "Memory";
    FWrap f("/proc/meminfo", "r");
    if (!f) return;
    Wrap<char *> cacheMemChar(1024);
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
        } else if (i == 1) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            freeMem = std::atoi(token) / 1024;
        } else if (i == 3) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            bufferMem = std::atoi(token) / 1024;
        } else if (i == 4) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            cacheMem = std::atoi(token) / 1024;
        } else if (i == 23) {
            char *token = strtok(cacheMemChar, ":");
            token = strtok(NULL, ":");
            token = strtok(token, " ");
            sReclaimable = std::atoi(token) / 1024;
            break;
        }
        i++;
    }
    // non-cache non-buffer non-reclaimable used memory
    int ncbrcUsedMem = totalMemNum - freeMem - bufferMem - cacheMem - sReclaimable;

    if (!bar) {
        content = std::to_string(ncbrcUsedMem) + "M / " + std::to_string(totalMemNum) + "M";
    } else {
        double memPercent = (double) ncbrcUsedMem / (double) totalMemNum * 100.0;
        content = ralsei::bar(15, lround(memPercent));
    }
}
