#include <sys/sysctl.h>
#include "utils/wrapper.hpp"

void ModelModule::fetch() {
    size_t len;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);
    Wrap<char *> model(len);
    sysctlbyname("hw.model", model, &len, NULL, 0);
    content = model.o;
    prefix = "Device";
}
