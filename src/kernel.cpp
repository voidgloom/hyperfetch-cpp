#include "kernel.hpp"

#if defined(__linux__)
    #include "impl/kernel/kernel_posix.cpp"
#elif defined(__APPLE__)
    #include "impl/kernel/kernel_posix.cpp"
#elif defined(_WIN32)
    #include "impl/kernel/kernel_win32.cpp"
#endif
