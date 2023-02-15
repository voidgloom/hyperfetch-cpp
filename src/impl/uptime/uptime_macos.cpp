#include <sys/sysctl.h>
#include <sys/time.h>
#include <chrono>

void UptimeModule::fetch() {
    auto curTime = std::chrono::system_clock::now();
    std::time_t timeAsTime_t = std::chrono::system_clock::to_time_t(curTime);
    struct timeval bootTime;
    size_t len = sizeof(bootTime);
    sysctlbyname("kern.boottime", &bootTime, &len, NULL, 0);
    uint64_t uptime = timeAsTime_t - bootTime.tv_sec;  
    int uptime_hours = uptime / 3600;
    int uptime_minutes = uptime % 3600 / 60;

    if (uptime_hours != 0)
        content = std::to_string(uptime_hours) + " hours, " + std::to_string(uptime_minutes) + " minutes";
    else
        content = std::to_string(uptime_minutes) + " minutes";

    prefix = "Uptime";
}
