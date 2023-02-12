#include <cstdio>
#include <cstring>
#include "utils/wrapper.hpp"

void ModelModule::fetch() {
  bool uses_devicetree = false;
  FWrap f("/sys/devices/virtual/dmi/id/product_name", "r");
  if (!f.f) {
    uses_devicetree = true;
    f.f = fopen("/sys/firmware/devicetree/base/model", "r");
  }
  fseek(f, 0, SEEK_END);
  size_t f_size = ftell(f);

  Wrap<char *> product_name(f_size);

  rewind(f);
  fgets(product_name, f_size, f);

  std::string finalValue = "";
  int i = 0;
  while (product_name[i] != '\0') {
    switch (product_name[i]) {
      case '\n':
        break;
      default:
        finalValue += product_name.o[i];
    }
    i++;
  }
  
  if (!uses_devicetree) {
    FWrap ver("/sys/devices/virtual/dmi/id/product_version", "r");
    fseek(ver, 0, SEEK_END);
    f_size = ftell(ver);

    Wrap<char *> product_version(f_size);

    rewind(f);
    fgets(product_version, f_size, f);

    // add a space
    finalValue += " ";
    i = 0;
    while (product_version[i] != '\0') {
      switch (product_version[i]) {
        case '\n':
          break;
        default:
          finalValue += product_version.o[i];
      }
      i++;
    }
  }
  prefix = "Device";
  content = finalValue;
}
