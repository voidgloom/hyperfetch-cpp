#include "distro.hpp"
#include "utils/osrelease.hpp"

void DistroModule::fetch() {
    OSReleaseParser parser;
    content = parser.getValue("PRETTY_NAME");
    prefix = "OS";
}
