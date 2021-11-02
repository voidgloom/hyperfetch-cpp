#include "cpu.hpp"
#include "utils/cpuid.hpp"

void CpuModule::fetch() {
    CpuInfo cpu;
    content = cpu.getValue("model name");
    prefix = "CPU";
}
