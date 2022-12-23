#include "ascii.hpp"
#include "osinfo.hpp"
#include <iostream>

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
        width = 0;
        height = 0;
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

    std::string asciiArtColor = "";
    const char *artColorEnv = std::getenv("HF_ASCII_COLOR");
    if (artColorEnv != NULL) {
        asciiArtColor = artColorEnv;
    }


    char *logo;
    if (asciiLogo == "arch") {
        std::string asciiFormat;
        if (artColorEnv == NULL) {
            asciiArtColor = "\033[38;5;6m";
        }
        if (smallLogoStr != "1") {
            logo =
                 "               -@\n"
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
        } else {
            logo =
               "       /\\\n"
			 "      /  \\\n"
			 "     /\\   \\\n"
			 "    /      \\\n"
			 "   /   ,,   \\\n"
			 "  /   |  |  -\\\n"
			 " /_-''    ''-_\\\033[0m";
            width = 16;
            height = 7;
        }
        std::cout << logo << std::endl;
    } else if (asciiLogo == "bedrock") {
        std::string asciiFormat;
        asciiArtColor = "\033[38;5;0m";
            logo =
                "\033[38;5;0m--------------------------------------\n\
\033[38;5;0m--------------------------------------\n\
\033[38;5;0m--------------------------------------\n\
\033[38;5;0m---\033[38;5;7m\\\\\\\\\\\\\\\\\\\\\\\\\033[38;5;0m-----------------------\n\
\033[38;5;0m----\033[38;5;7m\\\\\\      \\\\\\\033[38;5;0m----------------------\n\
\033[38;5;0m-----\033[38;5;7m\\\\\\      \\\\\\\033[38;5;0m---------------------\n\
\033[38;5;0m------\033[38;5;7m\\\\\\      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\033[38;5;0m------\n\
\033[38;5;0m-------\033[38;5;7m\\\\\\                    \\\\\\\033[38;5;0m-----\n\
\033[38;5;0m--------\033[38;5;7m\\\\\\                    \\\\\\\033[38;5;0m----\n\
\033[38;5;0m---------\033[38;5;7m\\\\\\        ______      \\\\\\\033[38;5;0m---\n\
\033[38;5;0m----------\033[38;5;7m\\\\\\                   ///\033[38;5;0m---\n\
\033[38;5;0m-----------\033[38;5;7m\\\\\\                 ///\033[38;5;0m----\n\
\033[38;5;0m------------\033[38;5;7m\\\\\\               ///\033[38;5;0m-----\n\
\033[38;5;0m-------------\033[38;5;7m\\\\\\////////////////\033[38;5;0m------\n\
\033[38;5;0m--------------------------------------\n\
\033[38;5;0m--------------------------------------\n\
\033[38;5;0m--------------------------------------\033[0m";

            width = 40;
            height = 17;
            puts(logo);
    } else {
        width = 0;
        height = 0;
    }
}
