//
// Created by orell on 7/21/20.
//
#include <iostream>
#include <client/Client.h>

class on_open {
public:
  void operator()() {}
};

class on_message {
public:
  void operator()() {}
};

class on_close {
public:
  void operator()() {}
};

int main() {
  EventHandler<on_message, on_open, on_close> handler;

  Client client{handler};
  std::cout << "Client main \n";
  return 0;
}