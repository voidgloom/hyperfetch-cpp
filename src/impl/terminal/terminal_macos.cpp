#include "utils/utils.hpp"

void TerminalModule::fetch() {
    prefix = "Terminal";
    content = util::getenv("TERM_PROGRAM");
}
