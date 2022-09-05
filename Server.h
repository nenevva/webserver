#pragma once

#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <functional>
#include <sys/epoll.h>
#include <vector>

#include "Socket.h"

using namespace std;

class Server
{
public:
    ServerSocket serverSocket;

    Server(int port);

    void run();

    static char *job(int conn_fd, char *buf, int msglen);
};