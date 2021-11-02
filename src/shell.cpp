#include "shell.hpp"
#include <cstring>

void ShellModule::fetch() {
  char* shellEnv = std::getenv("SHELL");
  // basename
  char *token = strtok(shellEnv, "/");
  std::string oldToken;
  while (token != NULL) {
    oldToken = token;
    token = strtok(NULL, "/");
  }

  content = oldToken;
  prefix = "Shell";
}
