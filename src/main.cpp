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

int asciiWidth;
int longestPrefix;
std::string prefixMode;

int main() {
  const char* infoChar = std::getenv("HF_INFO");
  std::string info;

  const char* prefixModeChar = std::getenv("HF_PREFIX_STYLE");
  if (prefixModeChar != NULL) {
    prefixMode = prefixModeChar;
  }

  AsciiArt ascii;
  ascii.print();

  asciiWidth = ascii.width;
  // return to top
  std::cout << "\033[" << ascii.height << "A";

  if (infoChar != NULL) {
    info = infoChar;
  } else {
    info = "title distro kernel shell model uptime wm pkgs cpu mem disk";
  }

  std::list<HyperfetchModule> module_list;

  std::string word;
  std::string newWord;
  std::stringstream iss(info);

  while (iss) {
    iss >> newWord;
    if (word != newWord) {
    word = newWord;
    if (word == "title") {
      TitleModule module;
      if (longestPrefix < 0) longestPrefix = 0;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "kernel") {
      KernelModule module;
      if (longestPrefix < 6) longestPrefix = 6;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "shell") {
      ShellModule module;
      if (longestPrefix < 5) longestPrefix = 5;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "model") {
      ModelModule module;
      if (longestPrefix < 5) longestPrefix = 5;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "distro") {
      DistroModule module;
      if (longestPrefix < 2) longestPrefix = 2;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "uptime") {
      UptimeModule module;
      if (longestPrefix < 6) longestPrefix = 6;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "wm") {
      WmModule module;
      if (longestPrefix < 2) longestPrefix = 2;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "pkgs") {
      PackageModule module;
      if (longestPrefix < 4) longestPrefix = 4;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "cpu") {
      CpuModule module;
      if (longestPrefix < 3) longestPrefix = 3;
      module.fetch();
      module_list.push_back(module);
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
    }
    }
  }

  int info_amount = 0;
  for (HyperfetchModule m : module_list) {
    m.print();
    info_amount++;
  }

  if (ascii.height != 0)
    std::cout << "\033[" << ascii.height - info_amount << "B";

  return 0;
}
