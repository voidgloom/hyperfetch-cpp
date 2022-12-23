#include "model.hpp"

#ifdef __linux__
    #include "impl/model/model_linux.cpp"
#elifdef __APPLE__
    #include "impl/model/model_macos.cpp"
#endif