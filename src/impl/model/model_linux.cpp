#include <cstdio>
#include <cstring>

void ModelModule::fetch() {
  FILE *f = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
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

  prefix = "Device";
  content = finalValue;

  delete[] product_name;
  delete[] product_version;
}
