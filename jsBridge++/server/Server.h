//
// Created by orell on 7/21/20.
//

#ifndef JSBRIDGE_JSBRIDGE_LIB_SERVER_SERVER_H_
#define JSBRIDGE_JSBRIDGE_LIB_SERVER_SERVER_H_

#include <iostream>

#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using ws_server =  websocketpp::server<websocketpp::config::asio>;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef ws_server::message_ptr message_ptr;

// Define a callback to handle incoming messages
void on_message(ws_server* s, const websocketpp::connection_hdl hdl, const message_ptr msg) {
  std::cout << "on_message called with hdl: " << hdl.lock().get()
            << " and message: " << msg->get_payload()
            << "\n";

  // check for a special command to instruct the server to stop listening so
  // it can be cleanly exited.
  if (msg->get_payload() == "stop") {
    s->stop();
    return;
  }

  try {
    s->send(hdl, msg->get_payload(), msg->get_opcode());
  } catch (websocketpp::exception const & e) {
    std::cout << "Echo failed because: "
              << "(" << e.what() << ")" << std::endl;
  }
}

class Server {
public:

public:
  explicit Server(){
    // Set logging settings
    //endpoint.set_error_channels(websocketpp::log::elevel::all);
    //endpoint.set_access_channels(websocketpp::log::alevel::frame_payload);
    endpoint.set_access_channels(websocketpp::log::alevel::all);
    endpoint.clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    endpoint.init_asio();
    endpoint.set_message_handler(bind(&on_message,&endpoint,::_1,::_2));
  }

  void run(const uint32_t port) {
    endpoint.listen(port);

    // Queues a connection accept operation
    endpoint.start_accept();

    // Start the Asio io_service run loop
    endpoint.run();
  }

private:
  ws_server endpoint;
};



#endif//JSBRIDGE_JSBRIDGE_LIB_SERVER_SERVER_H_
