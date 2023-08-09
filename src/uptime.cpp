#include "uptime.hpp"

#ifdef __linux__
    #include "impl/uptime/uptime_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/uptime/uptime_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/uptime/uptime_win32.cpp"
#endif