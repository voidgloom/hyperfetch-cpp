#include <sys/sysctl.h>
#include <string>

std::string OsInfo::getOsType() {
    return "macOS";
}

std::string OsInfo::getOsName() {
    return "macOS " + getOsVer();
}

std::string OsInfo::getOsVer() {
    char *osVerString;
    size_t len;
    sysctlbyname("kern.osproductversion", NULL, &len, NULL, 0);
    osVerString = (char *) malloc(len);
    sysctlbyname("kern.osproductversion", osVerString, &len, NULL, 0);
    std::string returnVal = "";
    returnVal += osVerString;
    free(osVerString);
    return returnVal;
}