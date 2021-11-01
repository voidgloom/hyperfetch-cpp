#include "title.hpp"
#include <iostream>
#include <sys/utsname.h>

void TitleModule::print() {
  std::cout << content << std::endl;
}

void TitleModule::fetch() {
  std::string username = std::getenv("USER");
  utsname unameResult;
  uname(&unameResult);
  content = username + "@" + unameResult.nodename;
}
