#include <iostream>

#include "../../jsBridge++/client/Client.h"



int main(int argc, char* argv[]) {


    Client client("ws://localhost:9002");

    auto res = client.run();

    return res;
}