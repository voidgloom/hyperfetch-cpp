#include "uptime.hpp"
#include <sstream>
#include <iostream>
#include <sys/sysinfo.h>

void UptimeModule::fetch() {
    struct sysinfo info;
    sysinfo(&info);
    int uptime_hours = info.uptime / 3600;
    int uptime_minutes = info.uptime % 3600 / 60;

    std::string up_hours = std::to_string(uptime_hours);
    std::string up_minutes = std::to_string(uptime_minutes);

    if (uptime_hours != 0)
        content = up_hours + " hours, " + up_minutes + " minutes";
    else
        content = up_minutes + " minutes";

    prefix="Uptime";
}
