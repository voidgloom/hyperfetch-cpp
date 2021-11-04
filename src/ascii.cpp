#include "ascii.hpp"
#include "utils/osrelease.hpp"
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
         OSReleaseParser parser;
         asciiLogo = parser.getValue("ID");
    }

    std::string asciiArtColor = "";
    const char *artColorEnv = std::getenv("HF_ASCII_COLOR");
    if (artColorEnv != NULL) {
        asciiArtColor = artColorEnv;
    }


    std::string logo;

    if (asciiLogo == "arch") {
        std::string asciiFormat;
        if (artColorEnv == NULL) {
            asciiArtColor = "\033[38;5;6m";
        }
        if (smallLogoStr != "1") {
            logo =
              asciiArtColor +     "               -@\n"
               + asciiArtColor +  "              .##@\n"
               + asciiArtColor +  "             .####@\n"
               + asciiArtColor +  "             @#####@\n"
               + asciiArtColor +  "           . *######@\n"
               + asciiArtColor +  "          .##@o@#####@\n"
               + asciiArtColor +  "         /############@\n"
               + asciiArtColor +  "        /##############@\n"
               + asciiArtColor +  "       @######@**%######@\n"
               + asciiArtColor +  "      @######`     %#####o\n"
               + asciiArtColor +  "     @######@       ######%\n"
               + asciiArtColor +  "   -@#######h       ######@.`\n"
               + asciiArtColor + "  /#####h**``       `**%@####@\n"
               + asciiArtColor + " @H@*`                    `*%#@\n"
               + asciiArtColor +  "*`                            `*\033[0m";
            width = 34;
            height = 15;
        } else {
            logo =
             asciiArtColor +    "       /\\\n"
			 + asciiArtColor +  "      /  \\\n"
			 + asciiArtColor +  "     /\\   \\\n"
			 + asciiArtColor +  "    /      \\\n"
			 + asciiArtColor +  "   /   ,,   \\\n"
			 + asciiArtColor +  "  /   |  |  -\\\n"
			 + asciiArtColor +  " /_-''    ''-_\\\033[0m";
            width = 16;
            height = 7;
        }
        std::cout << logo << std::endl;
    } else {
        width = 0;
        height = 0;
    }
}
