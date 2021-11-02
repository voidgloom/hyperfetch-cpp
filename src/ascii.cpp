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

    std::string logo;

    if (asciiLogo == "arch") {
        std::string asciiFormat;

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
                "*`                            `*";
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
				" /_-''    ''-_\\";
            width = 16;
            height = 7;
        }
        std::cout << logo << std::endl;
    } else {
        width = 0;
        height = 0;
    }
}
