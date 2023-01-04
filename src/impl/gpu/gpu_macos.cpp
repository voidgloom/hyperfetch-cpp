#include <sys/sysctl.h>

void GpuModule::fetch() {
    #ifdef __aarch64__
    // if the machine has an apple soc just retrieve the cpu again
    char *cpu;
    size_t len;
    sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0);
    cpu = (char *) malloc(len);
    sysctlbyname("machdep.cpu.brand_string", cpu, &len, NULL, 0);

    content = cpu;
    free(cpu);
    #else
    content = "";
    #endif
    prefix = "GPU";
}
