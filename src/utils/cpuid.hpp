#include <map>
#include <string>
#include <cstdio>

class CpuInfo {
    private:
        bool isPartial = false;
        std::map<std::string, std::string> map;
    public:
        CpuInfo(bool partial);
        std::string getValue(std::string key);
};
