#include "shell.hpp"

void ShellModule::fetch() {
  std::string shellEnv = std::getenv("SHELL");
  content = shellEnv;
  prefix = "Shell";
}
