#include "osinfo.hpp"

#ifdef __linux__
    #include "impl/osinfo/osinfo_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/osinfo/osinfo_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/osinfo/osinfo_win32.cpp"
#endif