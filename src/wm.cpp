#include "wm.hpp"

#ifdef __linux__
    #include "impl/wm/wm_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/wm/wm_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/wm/wm_win32.cpp"
#endif