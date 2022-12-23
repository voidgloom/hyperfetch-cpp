#include "distro.hpp"
#include "osinfo.hpp"

void DistroModule::fetch() {
    OsInfo info;
    content = info.getOsName();
    prefix = "OS";
}
