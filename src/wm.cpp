#include "wm.hpp"

#ifdef __linux__
    #include "impl/wm/wm_linux.cpp"
#elifdef __APPLE__
    #include "impl/wm/wm_macos.cpp"
#endif