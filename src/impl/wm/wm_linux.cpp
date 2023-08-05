
#include <cstdlib>
#include <dirent.h>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <list>
#include "utils/wrapper.hpp"
#include "utils/fs.hpp"
#include "wmList.hpp"

void WmModule::fetch() {
    prefix = "WM";
    // Check if we are running under WSL (i.e. Windows)
    if (fs::exists("/mnt/wsl")) {
        content = "DWM.exe";
        return;
    }
    content = "unknown";
    uid_t currentUserId = geteuid();
    struct dirent *files;

    Wrap<char *> comm(64);
    strcat(comm, "/proc/");
    Wrap<char *> exe(64);
    strcat(exe, "/proc/");
    Wrap<char *> buffer(512);

    DWrap dir("/proc/");

    while(files = readdir(dir)) {
        if (files->d_name[0] >= '1' && files->d_name[0] <= '9') {
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
                readlink(exe, buffer, 512);
                int lastSlashPos = 0;
                buflen = strlen(buffer);
                for (int i = 0; i < buflen; i++) {
                    if (buffer[i] == '/')
                        lastSlashPos = i;
                }
                // unsafe {
                    char *basename = buffer.o + lastSlashPos + 1;
                // }
                if (wmList.count(basename)) {
                    content = wmList.find(basename)->second;
                    break;
                }            
            }
        }
    }

    
}
