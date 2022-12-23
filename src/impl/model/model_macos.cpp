#include <sys/sysctl.h>

void ModelModule::fetch() {
    char *model; 
    size_t len;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);
    model = (char *) malloc(len);
    sysctlbyname("hw.model", model, &len, NULL, 0);

    content = model;
    prefix = "Device";
}