#include "ascii.hpp"
#include "utils/osrelease.hpp"
#include <iostream>

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


    std::string asciiLogo = "";
    const char *asciiArtEnv = std::getenv("HF_ASCII_LOGO");
    if (asciiArtEnv != NULL) {
        asciiLogo = asciiArtEnv;
    }

    if (asciiLogo.empty()) {
        OSReleaseParser parser;
        asciiLogo = parser.getValue("ID");
    }

    if (asciiLogo == "arch") {
        const char *logo =
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
        std::cout << logo << std::endl;
    } else {
        width = 0;
        height = 0;
    }
}
