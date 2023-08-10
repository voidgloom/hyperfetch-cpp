#include <cstddef>
#include <cstdio>
#include <string>

namespace file {
    std::size_t get_file_size(FILE* f) {
        fseek(f, 0, SEEK_END);
        auto f_size = ftell(f);
        rewind(f);
        return f_size;
    }
}

namespace util {
    std::string getenv(std::string var) {
        const char* val = std::getenv(var.c_str());
        if (val == nullptr) {
            return "";
        } else {
            return std::string(val);
        }
    }
}