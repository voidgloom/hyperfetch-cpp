#include "title.hpp"
#include <sys/utsname.h>

void TitleModule::fetch() {
  std::string username = std::getenv("USER");
  char *titleFormat = std::getenv("HF_TITLE_FORMAT");
  std::string titleFormatString;
  if (titleFormat != NULL)
    titleFormatString = titleFormat;
  else
    titleFormatString = "\033[1m\033[38;5;3m";

  noSeperator = true;
  utsname unameResult;
  uname(&unameResult);
  content = titleFormatString + username + "\033[0m" + "@" + titleFormatString + unameResult.nodename + "\033[0m";
}
