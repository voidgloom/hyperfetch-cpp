#include <bits/types/FILE.h>
#include <cstddef>
#include <cstdio>

namespace file {
    std::size_t get_file_size(FILE* f) {
        fseek(f, 0, SEEK_END);
        auto f_size = ftell(f);
        rewind(f);
        return f_size;
    }
}