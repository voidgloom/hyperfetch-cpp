#include <map>
#include <string>
#include <cstdio>

class OSReleaseParser {
    private:
        static std::map<std::string, std::string> map;
    public:
        OSReleaseParser();
        std::string getValue(std::string key);
};
