#include "utils/cpuid.hpp"
#include "utils/wrapper.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "impl/cpu/cpu_fallback_model_list.hpp"
#include "utils/utils.hpp"

void CpuModule::fetch() {
    CpuInfo cpu(true);
    bool use_cache = false;
    // check for cached cpu model name and read it if it exists
    std::string cache_path = "/run/user/" + std::to_string(getuid()) + "/hyperfetch-cpp/cpu";
    FWrap f(cache_path.c_str(), "r");
    
    Wrap<char *> cpuModelName(1024);
    if (f.f) {
        struct stat sFile;
        stat(cache_path.c_str(), &sFile);
        if (sFile.st_size != 0) {
            fgets(cpuModelName, 1024, f);
        }
        use_cache = true;

    }
    // set content to cached cpu model name if it exists
    // if it doesn't parse /proc/cpuinfo and write the result into the cache
    if (use_cache) {
        content = cpuModelName.o;
    } else {
        content = cpu.getValue("model name");
        std::string cacheDir = "/run/user/" + std::to_string(getuid()) + "/hyperfetch-cpp";
        mkdir(cacheDir.c_str(), 0755);
        FWrap f(cache_path.c_str(), "w");
        if (f) {
            fputs(content.c_str(), f);
        }
    }
    // fallback if cpu type isn't in /proc/cpuinfo
    if (content == "") {
        #ifdef __aarch64__
        FWrap f("/sys/firmware/devicetree/base/model", "r");
        if (f.f) {
            Wrap<char *> model(1024);
            fgets(model, 1024, f);
            content = cpu_fallback_model_map[model.o];
        } else {
           content = "Unknown ARM CPU";
        }
        #endif
    }
    prefix = "CPU";
}
