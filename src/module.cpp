#include "module.hpp"
#include <iostream>

extern int asciiWidth;

void HyperfetchModule::print() {
  std::string seperator;
  if(noSeperator)
    seperator = "";
  else
    seperator = ": ";

  std::cout << "\033[" << asciiWidth << "C" << prefix << seperator << content << std::endl;
}
