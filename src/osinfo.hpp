#include <string>
#ifdef __linux__
#include "utils/osrelease.hpp"
#endif

class OsInfo {
    public:
        std::string getOsType();
        std::string getOsVer();
        std::string getOsName();
    private:
        #ifdef __linux__
        OSReleaseParser parser;
        #endif
        static std::string osType;
        static std::string osVer;
        static std::string osName;
};