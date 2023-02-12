#include <sys/sysctl.h>
#include <utils/wrapper.hpp>

void CpuModule::fetch() {
    size_t len;
    sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0);
    Wrap<char *> cpu(len);
    sysctlbyname("machdep.cpu.brand_string", cpu, &len, NULL, 0);
    content = cpu.o;
    prefix = "CPU";
}
