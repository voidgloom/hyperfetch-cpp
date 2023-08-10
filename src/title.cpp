#include "title.hpp"
#if defined (__unix__) || (defined (__APPLE__))
#include <sys/utsname.h>
#else
#include <windows.h>
// #include <winsock.h>
#endif
#include "utils/wrapper.hpp"
#include "utils/utils.hpp"


void TitleModule::fetch() {
  #ifndef _WIN32
    std::string username = util::getenv("USER");
  #else 
    Wrap<char *> username(1024);
    Wrap<char *> hostname(1024);
    // why does the windows api require a uint32_t pointer for the buffer length???????
    Wrap<long unsigned int*> bufLen(4);
    *bufLen.o = 1024;
    GetUserNameA(username, bufLen);
 //   gethostname(hostname, 1024);  
  #endif

  auto titleFormat = util::getenv("HF_TITLE_FORMAT");
  if (titleFormat == "") titleFormat = "\033[1;38;5;5;4m";

  noSeperator = true;
  #ifndef _WIN32
    utsname unameResult;
    uname(&unameResult);
    content = titleFormat + username + "\033[0m" + "@" + titleFormat + unameResult.nodename + "\033[0m";
  #else 
    content = titleFormat + username.o + "\033[0m" + "@" + titleFormat + "hostname.o" + "\033[0m";
  #endif
}
