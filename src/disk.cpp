#include "disk.hpp"
#include "utils/bar.hpp"
#include <sys/statvfs.h>
#include <cmath>

void DiskModule::fetch(bool bar) {
    struct statvfs stat;
    if (!statvfs("/", &stat)) {
        double available = stat.f_bfree * stat.f_frsize;
        double total = stat.f_blocks * stat.f_frsize;
        if (!bar) {
            content = std::to_string(lround((total - available) / (1024*1024*1024))) + "G / " + std::to_string(lround(total / (1024 * 1024 * 1024))) + "G (" + std::to_string(lround(((total - available) / total) * 100)) + "%)";
        } else {
            content = "( " + ralsei::bar(15, lround(((total - available) / total) * 100)) + ")";
        }
    } else {
        content = "unknown";
    }
    prefix = "Disk (/)";

}
