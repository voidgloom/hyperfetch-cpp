#include "uptime.hpp"
#include <sstream>
#include <iostream>
#include <sys/sysinfo.h>

void UptimeModule::fetch() {
    struct sysinfo info;
    std::string up_hours;
    std::string up_minutes;

    sysinfo(&info);
    int uptime_hours = info.uptime / 3600;
    int uptime_minutes = info.uptime % 3600 / 60;


    std::stringstream stream_hours;
    stream_hours << uptime_hours;
    stream_hours >> up_hours;

    std::stringstream stream_minutes;
    stream_minutes << uptime_minutes;
    stream_minutes >> up_minutes;

    if (uptime_hours != 0)
        content = up_hours + " hours, " + up_minutes + " minutes";
    else
        content = up_minutes + " minutes";

    prefix="Uptime";
}
