#include "de.hpp"

#if defined(__linux__)
    #include "impl/de/de_linux.cpp"
#elif defined(__APPLE__)
    #include "impl/de/de_macos.cpp"
#elif defined(_WIN32)
    #include "impl/de/de_win32.cpp"
#endif