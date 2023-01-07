void TerminalModule::fetch() {
    prefix = "Terminal";
    content = std::getenv("TERM_PROGRAM");
}
