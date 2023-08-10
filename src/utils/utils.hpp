#include <cstdio>
#include <cstddef>
#include <string>

namespace file {
    std::size_t get_file_size(FILE*);
}

namespace util {
    std::string getenv(std::string);
}
