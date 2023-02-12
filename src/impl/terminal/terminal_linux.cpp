#include <bits/types/FILE.h>
#include "utils/wrapper.hpp"
#include <cstdlib>
#include <dirent.h>
#include <string>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

std::string get_parent(std::string pid) {
    std::string pid_as_str = "/proc/";
    pid_as_str += pid;
    pid_as_str += "/stat";

    FWrap f(pid_as_str.c_str(), "r");
    Wrap<char *> buf(4096);
    fgets(buf, 4096, f);
    strtok(buf, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");
    char *ppid = strtok(NULL, " ");
    std::string retval = ppid;
    return retval;
}

std::string get_process_name(std::string pid) {
    std::string pid_as_str = "/proc/";
    pid_as_str += pid;
    pid_as_str += "/exe";
    Wrap<char *> buf(4096);
    readlink(pid_as_str.c_str(), buf, 4096);
    int lastSlashPos = 0;
    int buflen = strlen(buf);
    for (int i = 0; i < buflen; i++) {
        if (buf.o[i] == '/')
            lastSlashPos = i;
    }
    // unsafe {
        char *basename = buf.o + lastSlashPos + 1;
    // }
    std::string retval = basename;
    return retval;
}

void TerminalModule::fetch() {
    std::string term_pid = get_parent(get_parent("self"));
    prefix = "Terminal";
    content = get_process_name(term_pid);
}
