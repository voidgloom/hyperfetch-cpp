#include "ram.hpp"

#ifdef __linux__
    #include "impl/ram/ram_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/ram/ram_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/ram/ram_win32.cpp"    
#endif