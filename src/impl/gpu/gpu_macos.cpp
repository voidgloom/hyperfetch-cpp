#include <sys/sysctl.h>
#include "utils/wrapper.hpp"


void GpuModule::fetch() {
    #ifdef __aarch64__
    // if the machine has an apple soc just retrieve the cpu again
    size_t len;
    sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0);
    Wrap<char *> cpu(len);
    sysctlbyname("machdep.cpu.brand_string", cpu.o, &len, NULL, 0);

    content = cpu;
    #else
    content = "";
    #endif
    prefix = "GPU";
}
