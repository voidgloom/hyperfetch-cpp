
#include <cstdlib>
#include <dirent.h>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <list>
#ifdef __linux__
#include "wmList.hpp"
#endif

void WmModule::fetch() {
    std::list<std::string> processNames;
    #ifdef __linux__
    content = "unknown";
    uid_t currentUserId = geteuid();
    struct dirent *files;

    char *comm = new char[64];
    comm[0] = '\0';
    strcat(comm, "/proc/");
    char *exe = new char[64];
    exe[0] = '\0';
    strcat(exe, "/proc/");
    char *buffer = new char[4096];

    DIR *dir = opendir("/proc/");
    while((files = readdir(dir)) != NULL) {
        if (files->d_name[0] == '1'
            || files->d_name[0] == '2'
            || files->d_name[0] == '3'
            || files->d_name[0] == '4'
            || files->d_name[0] == '5'
            || files->d_name[0] == '6'
            || files->d_name[0] == '7'
            || files->d_name[0] == '8'
            || files->d_name[0] == '9') {
            comm[6] = '\0';
            strcat(comm, files->d_name);
            struct stat sFile;
            stat(comm, &sFile);
            if (sFile.st_uid == currentUserId) {
                int buflen = strlen(buffer);
                bzero(buffer, buflen);
                exe[6] = '\0';
                strcat(exe, files->d_name);
                strcat(exe, "/exe");
                readlink(exe, buffer, 4096);
                int lastSlashPos = 0;
                buflen = strlen(buffer);
                for (int i = 0; i < buflen; i++) {
                    if (buffer[i] == '/')
                        lastSlashPos = i;
                }
                // unsafe {
                    char *basename = buffer + lastSlashPos + 1;
                // }
                if (wmList.count(basename)) {
                    content = wmList.find(basename)->second;
                    break;
                }            
            }
        }
    }
    delete[] comm;
    delete[] buffer;
    delete[] exe;
    #else
    content = "unknown";
    #endif
    prefix = "WM";

}
