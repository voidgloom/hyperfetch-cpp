#include "model.hpp"
#include <cstdio>
#include <cstring>

void ModelModule::fetch() {
  FILE *f = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
  fseek(f, 0, SEEK_END);
  size_t f_size = ftell(f);

  char *product_name = new char[f_size];

  rewind(f);
  fgets(product_name, f_size, f);

  char *ptnewline = strstr(product_name, "\n");
  if (ptnewline != NULL)
    strncpy(ptnewline, "\0", 1);

  fclose(f);
  f = fopen("/sys/devices/virtual/dmi/id/product_version", "r");
  fseek(f, 0, SEEK_END);
  f_size = ftell(f);

  char *product_version = new char[f_size];

  rewind(f);
  fgets(product_name, f_size, f);

  ptnewline = strstr(product_version, "\n");
  if (ptnewline != NULL)
    strncpy(ptnewline, "\0", 1);


  prefix = "Device";
  content = product_name;
  content += product_version;

  delete[] product_name;
  delete[] product_version;
}
