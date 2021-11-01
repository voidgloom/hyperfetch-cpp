#include "module.hpp"
#include <iostream>

void HyperfetchModule::print() {
  std::string seperator;
  if(noSeperator)
    seperator = "";
  else
    seperator = ": ";

  std::cout << prefix << seperator << content << std::endl;
}
