#pragma once

#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <functional>
#include <sys/epoll.h>
#include <vector>

using namespace std;

class ServerSocket
{
public:
    sockaddr_in addr;
    int listen_fd;
    int epoll_fd;
    int server_port;

    ServerSocket(int port);

    ~ServerSocket();

    void bind();

    void listen();

    int accept();

    void close();
};