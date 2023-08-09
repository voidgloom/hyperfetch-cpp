#include "disk.hpp"
#include "utils/bar.hpp"
#ifndef _WIN32
    #include <sys/statvfs.h>
#endif
#include <cmath>
#include <cstdint>
#ifdef _WIN32
    #include <windows.h>
#endif


void DiskModule::fetch(bool bar) {
    uint64_t free_bytes = 0;
    uint64_t total_bytes = 0;
    #ifdef _WIN32
        GetDiskFreeSpaceExA("C:\\", nullptr, (PULARGE_INTEGER) &total_bytes, (PULARGE_INTEGER) &free_bytes);
    #else
        struct statvfs stat;
        statvfs("/", &stat);
        free_bytes = stat.f_bfree * stat.f_frsize;
        total_bytes = stat.f_blocks * stat.f_frsize;
    #endif
    double available = free_bytes;
    double total = total_bytes;
    if (!bar) {
        content = std::to_string(lround((total - available) / (1024*1024*1024))) + "G / " + std::to_string(lround(total / (1024 * 1024 * 1024))) + "G (" + std::to_string(lround(((total - available) / total) * 100)) + "%)";
    } else {
        content = "( " + ralsei::bar(15, lround(((total - available) / total) * 100)) + ")";
    }
    prefix = "Disk (/)";
}
