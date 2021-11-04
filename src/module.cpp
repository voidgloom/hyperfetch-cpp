#include "module.hpp"
#include <iostream>

extern int asciiWidth;
extern int longestPrefix;
extern std::string prefixMode;

void HyperfetchModule::print() {
  std::string prefixFormat;
  const char *prefixFormatEnv = std::getenv("HF_PREFIX_FORMAT");
  if (prefixFormatEnv != NULL)
    prefixFormat = prefixFormatEnv;
  else
    prefixFormat = "\033[1;38;5;5m";
  std::string seperator;
  if(noSeperator || prefixMode == "pfetch")
    seperator = "";
  else
    seperator = ": ";

  if (prefixMode == "pfetch") {
    int prefixLen = prefix.length();
    int i;
    if (prefixLen == 0)
      i = 0;
    else
      i = longestPrefix - prefixLen + 1;

    while (i != 0) {
      prefix += " ";
      i--;
    }
    std::cout << "\033[" << asciiWidth << "C" << prefixFormat << prefix << "\033[0m" << content << std::endl;
  } else {
    std::cout << "\033[" << asciiWidth << "C" << prefixFormat << prefix << "\033[0m" << seperator << content << std::endl;
  }
}
