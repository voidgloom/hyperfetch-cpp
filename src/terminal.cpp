#include "terminal.hpp"

#ifdef __linux__
    #include "impl/terminal/terminal_linux.cpp"
#elifdef __APPLE__
    #include "impl/terminal/terminal_macos.cpp"
#endif