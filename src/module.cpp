#include "module.hpp"
#include <iostream>

void HyperfetchModule::print() {
  std::cout << prefix << ": " << content << std::endl;
}
