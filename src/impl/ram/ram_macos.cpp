#include <sys/sysctl.h>
#include <string>
#include <mach/mach.h>
#include <mach/mach_vm.h>

void RamModule::fetch(bool bar) {
    prefix = "Memory";
    content = "Unknown";
}
