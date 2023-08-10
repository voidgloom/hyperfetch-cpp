#include "shell.hpp"
#include "utils/utils.hpp"
#include <cstring>
#include <sstream>
#include <vector>

void ShellModule::fetch() {
  auto shellEnv = util::getenv("SHELL");
  std::vector<std::string> tokens;
  std::string temp;

  std::stringstream stream(shellEnv);
  while (std::getline(stream, temp, '/')) {
    ;
  }

  content = temp;
  prefix = "Shell";
}
