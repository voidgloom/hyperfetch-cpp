#include "osinfo.hpp"

#ifdef __linux__
    #include "impl/osinfo/osinfo_linux.cpp"
#elifdef __APPLE__
    #include "impl/osinfo/osinfo_macos.cpp"
#endif