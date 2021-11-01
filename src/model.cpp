#include "model.hpp"
#include <cstdio>
#include <cstring>

void ModelModule::fetch() {
  FILE *f = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
  fseek(f, 0, SEEK_END);
  size_t f_size = ftell(f);

  char *model_contents = new char[f_size];

  rewind(f);
  fgets(model_contents, f_size, f);

  char *ptnewline = strstr(model_contents, "\n");
  if (ptnewline != NULL)
    strncpy(ptnewline, "\0", 1);

  prefix = "Device";
  content = model_contents;

  delete[] model_contents;
}
