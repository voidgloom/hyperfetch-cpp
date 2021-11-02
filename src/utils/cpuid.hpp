#include <map>
#include <string>
#include <cstdio>

class CpuInfo {
    private:
        std::map<std::string, std::string> map;
    public:
        CpuInfo();
        std::string getValue(std::string key);
};
