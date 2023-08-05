#include <cstdio>
#include <cstring>
#include "iostream"
#include "utils/wrapper.hpp"
#include "utils/utils.hpp"

void ModelModule::fetch() {
  bool uses_devicetree = false;
  FWrap f("/sys/devices/virtual/dmi/id/product_name", "r");
  if (!f.f) {
    uses_devicetree = true;
    f = fopen("/sys/firmware/devicetree/base/model", "r");
  }
  if (!f.f) {
    prefix = "Device";
    content = "unknown";
    return;
  }

  size_t f_size = file::get_file_size(f);
  Wrap<char *> product_name(f_size);
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
   
    f_size = file::get_file_size(ver);
    Wrap<char *> product_version(f_size);
    fgets(product_version, f_size, ver);

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
