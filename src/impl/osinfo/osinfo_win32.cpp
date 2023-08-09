#include <string>
#include <windows.h>
#include "utils/wrapper.hpp"
#include <iostream>
#ifdef _MSC_VER
    #define popen _popen
    #define pclose _pclose
#endif

std::string OsInfo::getOsName() {
    FILE *f;
    Wrap<char *> buf(1024);
    std::string retVal = "";
    if ((f = popen("wmic os get Caption", "r"))) {
        fgets(buf, 1024, f);
        fgets(buf, 1024, f);
        // remove Microsoft
        buf.o += 10;
        strtok(buf, "\n");
        retVal += buf.o;
        buf.o -= 10;
        pclose(f);
    }   
    return retVal;
}

std::string OsInfo::getOsVer() {
    return "";
}

std::string OsInfo::getOsType() {
    return "Win32";
}
