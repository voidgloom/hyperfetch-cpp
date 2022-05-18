#include "uptime.hpp"

#ifdef __linux__
    #include "impl/uptime/uptime_linux.cpp"
#elifdef __APPLE__
    #include "impl/uptime/uptime_macos.cpp"
#endif