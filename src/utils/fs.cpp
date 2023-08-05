#include "utils/wrapper.hpp"

// macOS < 10.15 does not implement std::filesystem
namespace fs {
    bool exists(const char* filename) {
        FWrap f(filename, "r");
        return f.f;
    }
}