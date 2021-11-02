#include "cpu.hpp"
#include "utils/cpuid.hpp"

void CpuModule::fetch() {
    CpuInfo cpu(true);
    content = cpu.getValue("model name");
    prefix = "CPU";
}
