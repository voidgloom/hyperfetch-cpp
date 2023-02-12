#include "wm.hpp"
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <list>
#include "deList.hpp"
#include "utils/wrapper.hpp"

void DeModule::fetch() {
    std::list<std::string> processNames;
    uid_t currentUserId = geteuid();
    struct dirent *files;
    content = "unknown";
    
    Wrap<char *> comm(64);
    strcat(comm, "/proc/");
    Wrap<char *> exe(64);
    strcat(exe, "/proc/");
    Wrap<char *> buffer(4096);

    DWrap dir("/proc/");
    
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
                exe.o[6] = '\0';
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
                    char *basename = buffer.o + lastSlashPos + 1;
                // }
                if (deList.count(basename)) {
                    content = deList.find(basename)->second;
                    break;
                }            
            }
        }
    }
    
    prefix = "DE";
}
