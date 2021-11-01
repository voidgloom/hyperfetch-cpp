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

int asciiWidth;

int main() {
  const char* infoChar = std::getenv("HF_INFO");
  std::string info;

  AsciiArt ascii;
  ascii.print();

  asciiWidth = ascii.width;
  // return to top
  std::cout << "\033[" << ascii.height << "A";

  if (infoChar != NULL) {
    info = infoChar;
  } else {
    info = "title distro kernel shell model uptime wm";
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
      module.fetch();
      module_list.push_back(module);
    } else if (word == "kernel") {
      KernelModule module;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "shell") {
      ShellModule module;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "model") {
      ModelModule module;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "distro") {
      DistroModule module;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "uptime") {
      UptimeModule module;
      module.fetch();
      module_list.push_back(module);
    } else if (word == "wm") {
      WmModule module;
      module.fetch();
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
