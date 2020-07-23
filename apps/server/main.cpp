//
// Created by orell on 7/21/20.
//
#include <iostream>
#include <server/Server.h>

int main() {
  Server server{};
  server.run(9002);
  return 0;
}