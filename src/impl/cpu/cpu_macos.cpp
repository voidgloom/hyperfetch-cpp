#include <sys/sysctl.h>

void CpuModule::fetch() {
    char *cpu; 
    size_t len;
    sysctlbyname("machdep.cpu.brand_string", NULL, &len, NULL, 0);
    cpu = (char *) malloc(len);
    sysctlbyname("machdep.cpu.brand_string", cpu, &len, NULL, 0);

    content = cpu;
    free(cpu);
    prefix = "CPU";
}