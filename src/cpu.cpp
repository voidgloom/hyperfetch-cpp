#include "cpu.hpp"

#ifdef __linux__
    #include "impl/cpu/cpu_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/cpu/cpu_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/cpu/cpu_win32.cpp"
#endif