#include "utils/cpuid.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void CpuModule::fetch() {
    CpuInfo cpu(true);
    // check for cached cpu model name and read it if it exists
    std::string cache_path = "/run/user/" + std::to_string(getuid()) + "/hyperfetch-cpp/cpu";
    FILE *f;
    char *cpuModelName = NULL;
    if ((f = fopen(cache_path.c_str(), "r"))) {
        cpuModelName = new char[1024];
        fgets(cpuModelName, 1024, f);
    }
    // set content to cached cpu model name if it exists
    // if it doesn't parse /proc/cpuinfo and write the result into the cache
    if (cpuModelName != NULL) {
        content = cpuModelName;
    } else {
        content = cpu.getValue("model name");
        std::string cacheDir = "/run/user/" + std::to_string(getuid()) + "/hyperfetch-cpp";
        mkdir(cacheDir.c_str(), 0755);
        FILE *f;
        if ((f = fopen(cache_path.c_str(), "w"))) {
            fputs(content.c_str(), f);
        }
    }
    prefix = "CPU";
}
