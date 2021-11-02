#include "module.hpp"
#include <iostream>

extern int asciiWidth;
extern int longestPrefix;
extern std::string prefixMode;

void HyperfetchModule::print() {
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
    std::cout << "\033[" << asciiWidth << "C" << prefix << content << std::endl;
  } else {
    std::cout << "\033[" << asciiWidth << "C" << prefix << seperator << content << std::endl;
  }
}
