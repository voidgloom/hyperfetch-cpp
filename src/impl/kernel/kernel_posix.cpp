#include "module.hpp"
#include <sys/utsname.h>

void KernelModule::fetch() {
      utsname unameResult;
      uname(&unameResult);
      content = unameResult.release;
      prefix = "Kernel";
}
