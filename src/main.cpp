#include <thread>
#include <iostream>
#include "kernel.hpp"
#include "shell.hpp"
#include "model.hpp"
#include "title.hpp"

int main() {
  TitleModule tm;
  KernelModule km;
  ShellModule sm;
  ModelModule mm;

  tm.fetch();
  km.fetch();
  sm.fetch();
  mm.fetch();

  tm.print();
  km.print();
  sm.print();
  mm.print();
  return 0;
}
