#include "disk.hpp"
#include <sys/statvfs.h>
#include <cmath>

void DiskModule::fetch() {
    struct statvfs stat;
    if (!statvfs("/", &stat)) {
        double available = stat.f_bfree * stat.f_frsize;
        double total = stat.f_blocks * stat.f_frsize;
        content = std::to_string(lround((total - available) / (1024*1024*1024))) + "G / " + std::to_string(lround(total / (1024 * 1024 * 1024))) + "G (" + std::to_string(lround(((total - available) / total) * 100)) + "%)";
    } else {
        content = "unknown";
    }
    prefix = "Disk (/)";

}
