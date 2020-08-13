//
// Created by orell on 7/21/20.
//

// TODO: client segfaults at the moment when connection is closed -> we need to handle this

#ifndef JSBRIDGE_JSBRIDGE_LIB_CLIENT_CLIENT_H_
#define JSBRIDGE_JSBRIDGE_LIB_CLIENT_CLIENT_H_

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <utility>

class Client;

using client = websocketpp::client<websocketpp::config::asio_client>;

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;


// pull out the type of messages sent by our config
using message_ptr = websocketpp::config::asio_client::message_type::ptr;


class Client {
public:
  std::string uri;
  client cl = client();

  explicit Client(const std::string uri) : uri(uri) {  }

  int run() {
    try {
      // Set logging to be pretty verbose (everything except message payloads)
      cl.set_access_channels(websocketpp::log::alevel::all);
      cl.clear_access_channels(websocketpp::log::alevel::frame_payload);

      // Initialize ASIO
      cl.init_asio();

      // Register our handlers
      cl.set_open_handler(websocketpp::lib::bind(&Client::on_open, this,::_1));
      cl.set_message_handler(websocketpp::lib::bind(&Client::on_message, this, ::_1,::_2));

      websocketpp::lib::error_code ec;
      client::connection_ptr con = cl.get_connection(uri, ec);
      if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
        return -1;
      }

      // Note that connect here only requests a connection. No network messages are
      // exchanged until the event loop starts running in the next line.
      cl.connect(con);

      // Start the ASIO io_service run loop
      // this will cause a single connection to be made to the server. c.run()
      // will exit when this connection is closed.
      cl.run();
    } catch (websocketpp::exception const & e) {
      std::cout << e.what() << std::endl;
    }
    return 0;
  }

  // This message handler will be invoked once for each incoming message. It
// prints the message and then sends a copy of the message back to the server.
  void on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;


    websocketpp::lib::error_code ec;

    cl.send(hdl, msg->get_payload(), msg->get_opcode(), ec);
    if (ec) {
      std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
  }

  // This handler will be invoked once the connection to the server is opened
// after the initial messages (registration + hello) all incoming messages are being echoed back
  void on_open(websocketpp::connection_hdl hdl) {
    // register as the game

    std::string msg = "game";
    cl.send(hdl,msg,websocketpp::frame::opcode::text);
    cl.get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);

    // send some data to the user via the bridge server
    msg = "Hi from game!";
    cl.send(hdl,msg,websocketpp::frame::opcode::text);
    cl.get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);
  }
};

#endif//JSBRIDGE_JSBRIDGE_LIB_CLIENT_CLIENT_H_
