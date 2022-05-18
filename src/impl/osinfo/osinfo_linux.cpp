#include <string>

std::string OsInfo::getOsName() {
    return parser.getValue("PRETTY_NAME");
}

std::string OsInfo::getVer() {
    return "";
}

std::string OsInfo::getOsType() {
    return parser.getValue("ID");
}