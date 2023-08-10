#include <cstring>
#include <sstream>
#include <iostream>
#include <list>
#include "kernel.hpp"
#include "shell.hpp"
#include "model.hpp"
#include "title.hpp"
#include "distro.hpp"
#include "ascii.hpp"
#include "uptime.hpp"
#include "wm.hpp"
#include "package.hpp"
#include "cpu.hpp"
#include "ram.hpp"
#include "disk.hpp"
#include "de.hpp"
#include "gpu.hpp"
#include "terminal.hpp"
#include "utils/utils.hpp"
#ifdef _WIN32
#include <windows.h>
#endif

int asciiWidth;
int longestPrefix;
std::string prefixMode;

#define Module(klass, prefixLength) klass module; if (longestPrefix < prefixLength) longestPrefix = prefixLength; module.fetch(); module_list.push_back(module)

int main() {
  #ifdef _WIN32
    // Windows expects ASCII by default, so you have to set stdout to accept UTF-8
    SetConsoleOutputCP(CP_UTF8);
  #endif

  prefixMode = util::getenv("HF_PREFIX_STYLE");

  AsciiArt ascii;
  ascii.print();

  asciiWidth = ascii.width;
  // return to top
  std::cout << "\033[" << ascii.height << "A\033[" << ascii.width << "D";

  std::list<HyperfetchModule> module_list;

  std::string info = util::getenv("HF_INFO");

  if (info == "") {
    info = "title distro kernel shell model uptime wm de pkgs cpu gpu terminal mem_bar disk_bar";
  }

  std::string word;
  std::string newWord;
  std::stringstream iss(info);

  while (iss) {
    iss >> newWord;
    if (word != newWord) {
    word = newWord;
    if (word == "title") {
      Module(TitleModule, 0);
    } else if (word == "kernel") {
      Module(KernelModule, 6);
    } else if (word == "shell") {
      Module(ShellModule, 5);
    } else if (word == "model") {
      Module(ModelModule, 5);
    } else if (word == "distro") {
      Module(DistroModule, 2);
    } else if (word == "uptime") {
      Module(UptimeModule, 6);
    } else if (word == "wm") {
      Module(WmModule, 2);
    } else if (word == "pkgs") {
      Module(PackageModule, 4);
    } else if (word == "cpu") {
      Module(CpuModule, 3);
    } else if (word == "mem") {
      RamModule module;
      if (longestPrefix < 6) longestPrefix = 6;
      module.fetch(false);
      module_list.push_back(module);
    } else if (word == "disk") {
      DiskModule module;
      if (longestPrefix < 8) longestPrefix = 8;
      module.fetch(false);
      module_list.push_back(module);
    } else if (word == "disk_bar") {
      DiskModule module;
      if (longestPrefix < 8) longestPrefix = 8;
      module.fetch(true);
      module_list.push_back(module);
    } else if (word == "mem_bar") {
      RamModule module;
      if (longestPrefix < 6) longestPrefix = 6;
      module.fetch(true);
      module_list.push_back(module);
    } else if (word == "de") {
      Module(DeModule, 2);
    } else if (word == "gpu") {
      Module(GpuModule, 3);
    } else if (word == "terminal") {
      Module(TerminalModule, 8);
    } 
    }
  }

  int info_amount = 0;
  for (HyperfetchModule m : module_list) {
    m.print();
    info_amount++;
  }
  
  std::string show_color = util::getenv("HF_SHOW_COLORS");

  if (show_color != "0") {
    std::cout << "\n\033[" << asciiWidth << "C" 
              << "\033[48;5;0m   \033[48;5;1m   \033[48;5;2m   \033[48;5;3m   \033[48;5;4m   \033[48;5;5m   \033[48;5;6m   \033[48;5;7m   \033[0m\n"
    << "\033[" << asciiWidth << "C\033[48;5;8m   \033[48;5;9m   \033[48;5;10m   \033[48;5;11m   \033[48;5;12m   \033[48;5;13m   \033[48;5;14m   \033[48;5;15m   \033[0m"
    << std::endl;
  }

  if (ascii.height != 0)
    std::cout << "\033[" << ascii.height - info_amount << "B";

  return 0;
}
