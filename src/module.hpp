#ifndef MODULE
#define MODULE
#include <string>

class HyperfetchModule {
  public:
    std::string content;
    std::string prefix;
    void print();
    void fetch();
};
#endif
