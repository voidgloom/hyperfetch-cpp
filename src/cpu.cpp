#include "cpu.hpp"

#ifdef __linux__
    #include "impl/cpu/cpu_linux.cpp"
#elifdef __APPLE__
    #include "impl/cpu/cpu_macos.cpp"
#endif