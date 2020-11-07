//
// Created by orell on 7/21/20.
//

#ifndef JSBRIDGE_JSBRIDGE_LIB_CLIENT_CLIENT_H_
#define JSBRIDGE_JSBRIDGE_LIB_CLIENT_CLIENT_H_

#include <iostream>


template <typename OnMessage, typename OnOpen, typename OnClose>
class EventHandler {
public:
  using on_message_handler = OnMessage;
  using on_open_handler = OnOpen;
  using on_close_handler = OnClose;

  // needs to be given a connection or a endpoint in order to register the handler there
  // connection/endpoint should be an overload
  void register_handler() const {};
};

/*
 * One could either make the whole Client class a template and define a handler object
 */
template<typename EH>
class Client {
private:
  const EH& event_handler;
public:
  Client(const EH& handler) : event_handler(handler) {
    handler.register_handler();

    std::cout << "-> Constructed client! \n";
  }


};

#endif//JSBRIDGE_JSBRIDGE_LIB_CLIENT_CLIENT_H_
