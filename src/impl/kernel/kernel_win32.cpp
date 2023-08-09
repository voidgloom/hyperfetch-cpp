#include "module.hpp"
#include "utils/wrapper.hpp"
#include <windows.h>

void KernelModule::fetch() {
    Wrap<LPOSVERSIONINFOA> verInfo(1024);
    GetVersionExA(verInfo);
    content += verInfo.o->dwMajorVersion;
    content += verInfo.o->dwMinorVersion;
    prefix = "Kernel";
}
