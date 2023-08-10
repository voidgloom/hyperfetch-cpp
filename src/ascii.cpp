#include "ascii.hpp"
#include "osinfo.hpp"
#include "utils/utils.hpp"
#include <cstring>
#include <iostream>
#ifdef _MSC_VER
    #include <windows.h>
#endif

/*
* ASCII art either official, from neofetch or from pfetch
*/

void AsciiArt::print() {
    auto printAscii = util::getenv("HF_ASCII");

    if (printAscii == "0") {
        width = -1;
        height = -1;
        return;
    }

    auto smallLogo = util::getenv("HF_SMALL_LOGO");

    auto asciiLogo = util::getenv("HF_ASCII_LOGO");
    if (asciiLogo == "") {
         OsInfo info;
         asciiLogo = info.getOsType();
    }

    if (asciiLogo == "arch" || asciiLogo == "archarm") {
        if (smallLogo != "1") {
            const char *logo =
                 "\033[38;5;6m               -@\n"
                 "              .##@\n"
                 "             .####@\n"
                 "             @#####@\n"
                 "           . *######@\n"
                 "          .##@o@#####@\n"
                 "         /############@\n"
                 "        /##############@\n"
                 "       @######@**%######@\n"
                 "      @######`     %#####o\n"
                 "     @######@       ######%\n"
                 "   -@#######h       ######@.`\n"
                 "  /#####h**``       `**%@####@\n"
                 " @H@*`                    `*%#@\n"
                 "*`                            `*\033[0m";
            width = 34;
            height = 14;
            fwrite(logo, strlen(logo), 1, stdout);
        } else {
            const char *logo =
               "\033[38;5;6m       /\\\n"
			 "      /  \\\n"
			 "     /\\   \\\n"
			 "    /      \\\n"
			 "   /   ,,   \\\n"
			 "  /   |  |  -\\\n"
			 " /_-''    ''-_\\\033[0m";
            width = 16;
            height = 7;
            fwrite(logo, strlen(logo), 1, stdout);
        }
    } else if (asciiLogo == "bedrock") {
        const char *logo =
                "\033[38;5;0m--------------------------------------\n\
--------------------------------------\n\
--------------------------------------\n\
---\033[38;5;7m\\\\\\\\\\\\\\\\\\\\\\\\\033[38;5;0m-----------------------\n\
----\033[38;5;7m\\\\\\      \\\\\\\033[38;5;0m----------------------\n\
-----\033[38;5;7m\\\\\\      \\\\\\\033[38;5;0m---------------------\n\
------\033[38;5;7m\\\\\\      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\033[38;5;0m------\n\
-------\033[38;5;7m\\\\\\                    \\\\\\\033[38;5;0m-----\n\
--------\033[38;5;7m\\\\\\                    \\\\\\\033[38;5;0m----\n\
---------\033[38;5;7m\\\\\\        ______      \\\\\\\033[38;5;0m---\n\
----------\033[38;5;7m\\\\\\                   ///\033[38;5;0m---\n\
-----------\033[38;5;7m\\\\\\                 ///\033[38;5;0m----\n\
------------\033[38;5;7m\\\\\\               ///\033[38;5;0m-----\n\
-------------\033[38;5;7m\\\\\\////////////////\033[38;5;0m------\n\
--------------------------------------\n\
--------------------------------------\n\
--------------------------------------\033[0m\n";

            width = 40;
            height = 17;
            fwrite(logo, strlen(logo), 1, stdout);
    } else {
        width = -1;
        height = -1;
    }
}
