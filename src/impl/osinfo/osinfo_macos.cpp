#include <sys/sysctl.h>
#include "utils/wrapper.hpp"
#include <string>

std::string OsInfo::getOsType() {
    return "macOS";
}

std::string OsInfo::getOsName() {
    return "macOS " + getOsVer();
}

std::string OsInfo::getOsVer() {
    size_t len;
    sysctlbyname("kern.osproductversion", NULL, &len, NULL, 0);
    Wrap<char *> osVerString(len);
    sysctlbyname("kern.osproductversion", osVerString, &len, NULL, 0);
    std::string returnVal = osVerString.o;
    return returnVal;
}
