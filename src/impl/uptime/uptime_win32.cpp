#include <windows.h>

void UptimeModule::fetch() {
    unsigned long long secs = GetTickCount64() / 1000;
    int uptime_hours = secs / 3600;
    int uptime_minutes = secs % 3600 / 60;

    if (uptime_hours != 0)
        content = std::to_string(uptime_hours) + " hours, " + std::to_string(uptime_minutes) + " minutes";
    else
        content = std::to_string(uptime_minutes) + " minutes";

    prefix="Uptime";
}