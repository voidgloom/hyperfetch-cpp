#include "title.hpp"
#if defined (__unix__) || (defined (__APPLE__))
#include <sys/utsname.h>
#else
#include <windows.h>
// #include <winsock.h>
#endif
#include "utils/wrapper.hpp"


void TitleModule::fetch() {
  #ifndef _WIN32
    std::string username = std::getenv("USER");
  #else 
    Wrap<char *> username(1024);
    Wrap<char *> hostname(1024);
    // why does the windows api require a uint32_t pointer for the buffer length???????
    Wrap<long unsigned int*> bufLen(4);
    *bufLen.o = 1024;
    GetUserNameA(username, bufLen);
 //   gethostname(hostname, 1024);  
  #endif

  char *titleFormat = std::getenv("HF_TITLE_FORMAT");
  std::string titleFormatString;
  if (titleFormat != NULL)
    titleFormatString = titleFormat;
  else
    titleFormatString = "\033[1;38;5;5;4m";

  noSeperator = true;
  #ifndef _WIN32
    utsname unameResult;
    uname(&unameResult);
    content = titleFormatString + username + "\033[0m" + "@" + titleFormatString + unameResult.nodename + "\033[0m";
  #else 
    content = titleFormatString + username.o + "\033[0m" + "@" + titleFormatString + "hostname.o" + "\033[0m";
  #endif
}
