#include <iostream>

#include "Server.h"

using namespace std;

int main() {
    cout << "using port 8088, server is ready to run" << endl;
    Server server(8088);
    server.run();
}