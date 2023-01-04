#include "gpu.hpp"

#if defined(__linux__)
    #include "impl/gpu/gpu_linux.cpp"
#elif defined(__APPLE__)
    #include "impl/gpu/gpu_macos.cpp"
#endif
