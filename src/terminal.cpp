#include "terminal.hpp"

#ifdef __linux__
    #include "impl/terminal/terminal_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/terminal/terminal_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/terminal/terminal_win32.cpp"
#endif