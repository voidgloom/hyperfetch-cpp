#include "ascii.hpp"
#include "osinfo.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>

/*
* ASCII art either official, from neofetch or from pfetch
*/

void AsciiArt::print() {
    const char *printAscii = std::getenv("HF_ASCII");
    std::string pAscii = "";
    if (printAscii != NULL) {
        pAscii = printAscii;
    }

    if (pAscii == "0") {
        width = -1;
        height = -1;
        return;
    }

    const char *smallLogo = std::getenv("HF_SMALL_LOGO");
        std::string smallLogoStr;
        if (smallLogo != NULL)
            smallLogoStr = smallLogo;
        else
            smallLogoStr = "";

    std::string asciiLogo = "";
    const char *asciiArtEnv = std::getenv("HF_ASCII_LOGO");
    if (asciiArtEnv != NULL) {
        asciiLogo = asciiArtEnv;
    } else {
         OsInfo info;
         asciiLogo = info.getOsType();
    }

    if (asciiLogo == "arch") {
        if (smallLogoStr != "1") {
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
            height = 15;
            write(0, logo, strlen(logo));
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
            write(0, logo, strlen(logo));
        }
    } else if (asciiLogo == "bedrock") {
        std::string asciiFormat;
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
            write(0, logo, strlen(logo));
    } else {
        width = 0;
        height = 0;
    }
}
