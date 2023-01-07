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
    return strdup(basename);
}

void TerminalModule::fetch() {
    FILE *f = fopen("/proc/self/stat", "r");
    char *buf = new char[4096];
    fgets(buf, 4096, f);
    fclose(f);
    strtok(buf, " ");
    strtok(NULL, " ");
    strtok(NULL, " ");
    std::string ppid = strtok(NULL, " ");
    std::string term_pid = get_parent(ppid);
    
    delete[] buf;
    
    prefix = "Terminal";
    content = get_process_name(term_pid);
}