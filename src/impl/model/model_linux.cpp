#include <cstdio>
#include <cstring>

void ModelModule::fetch() {
  bool uses_devicetree = false;
  FILE *f = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
  if (f == NULL) {
    uses_devicetree = true;
    f = fopen("/sys/firmware/devicetree/base/model", "r");
  }
  fseek(f, 0, SEEK_END);
  size_t f_size = ftell(f);

  char *product_name = new char[f_size];

  rewind(f);
  fgets(product_name, f_size, f);

  std::string finalValue = "";
  int i = 0;
  while (product_name[i] != '\0') {
    switch (product_name[i]) {
      case '\n':
        break;
      default:
        finalValue += product_name[i];
    }
    i++;
  }
  
  fclose(f);
  if (!uses_devicetree) {
    f = fopen("/sys/devices/virtual/dmi/id/product_version", "r");
    fseek(f, 0, SEEK_END);
    f_size = ftell(f);

    char *product_version = new char[f_size];

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
          finalValue += product_version[i];
      }
      i++;
    }
    delete[] product_version;
  }
  prefix = "Device";
  content = finalValue;

  delete[] product_name;
}
