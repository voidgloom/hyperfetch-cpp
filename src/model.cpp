#include "model.hpp"

#ifdef __linux__
    #include "impl/model/model_linux.cpp"
#endif
#ifdef __APPLE__
    #include "impl/model/model_macos.cpp"
#endif
#ifdef _WIN32
    #include "impl/model/model_win32.cpp"
#endif