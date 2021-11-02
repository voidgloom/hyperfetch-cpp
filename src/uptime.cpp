#include "uptime.hpp"
#include <sys/sysinfo.h>

void UptimeModule::fetch() {
    struct sysinfo info;
    sysinfo(&info);
    int uptime_hours = info.uptime / 3600;
    int uptime_minutes = info.uptime % 3600 / 60;

    if (uptime_hours != 0)
        content = std::to_string(uptime_hours) + " hours, " + std::to_string(uptime_minutes) + " minutes";
    else
        content = std::to_string(uptime_minutes) + " minutes";

    prefix="Uptime";
}
