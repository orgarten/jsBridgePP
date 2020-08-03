//
// Created by orell on 7/21/20.
//
#include <iostream>
#include <bridge/Bridge.h>

int main() {
  Bridge server{};
  server.run(9002);
  return 0;
}