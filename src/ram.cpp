#include "ram.hpp"

#ifdef __linux__
    #include "impl/ram/ram_linux.cpp"
#elifdef __APPLE__
    #include "impl/ram/ram_macos.cpp"
#endif