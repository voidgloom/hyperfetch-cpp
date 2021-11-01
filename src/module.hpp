#ifndef MODULE
#define MODULE
#include <string>
#

class HyperfetchModule {
  public:
    bool noSeperator = false;
    std::string content;
    std::string prefix;
    void print();
    void fetch();
};
#endif
