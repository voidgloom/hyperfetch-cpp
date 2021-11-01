#include <thread>
#include <sstream>
#include <iostream>
#include <list>
#include "kernel.hpp"
#include "shell.hpp"
#include "model.hpp"
#include "title.hpp"
#include "distro.hpp"
#include "ascii.hpp"

int asciiWidth;
int asciiHeight;

int main() {
  const char* infoChar = std::getenv("HF_INFO");
  std::string info;

  AsciiArt ascii;
  ascii.print();


  if (infoChar != NULL) {
    info = infoChar;
  } else {
    info = "title distro kernel shell model";
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
    }
    }
  }

  for (HyperfetchModule m : module_list) {
    m.print();
  }

  return 0;
}
