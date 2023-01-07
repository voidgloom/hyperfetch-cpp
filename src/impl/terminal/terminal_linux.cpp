#include <bits/types/FILE.h>
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

    FILE *f = fopen(pid_as_str.c_str(), "r");
    char *buf = new char[4096];
    bzero(buf, strlen(buf));
    fgets(buf, 4096, f);
    fclose(f);
    strtok(buf, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");
    char *ppid = strtok(NULL, " ");
    std::string retval = ppid;
    delete[] buf;
    return retval;
}

std::string get_process_name(std::string pid) {
    std::string pid_as_str = "/proc/";
    pid_as_str += pid;
    pid_as_str += "/exe";
    char *buf = new char[4096];
    bzero(buf, 4096);
    readlink(pid_as_str.c_str(), buf, 4096);
    int lastSlashPos = 0;
    int buflen = strlen(buf);
    for (int i = 0; i < buflen; i++) {
        if (buf[i] == '/')
            lastSlashPos = i;
    }
    // unsafe {
        char *basename = buf + lastSlashPos + 1;
    // }
    std::string retval = strdup(basename);
    delete[] buf;
    return retval;
}

void TerminalModule::fetch() {
    std::string term_pid = get_parent(get_parent("self"));
    prefix = "Terminal";
    content = get_process_name(term_pid);
}