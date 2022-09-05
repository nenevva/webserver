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
#include <cstring>

#include "Socket.h"
#include "Util.h"

using namespace std;

ServerSocket::ServerSocket(int port) {
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    setReusePort(listen_fd);
    setNonBlocking(listen_fd);
}

void ServerSocket::bind() {
    ::bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr));
}

void ServerSocket::listen() {
    ::listen(listen_fd, 1024);
}

int ServerSocket::accept() {
    int conn_fd = ::accept(listen_fd, NULL, NULL);
    if (conn_fd < 0) {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return conn_fd;
        std::cout << "accept error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        std::cout << "conn_fd:" << conn_fd << std::endl;
        perror("accept error");
    }
    return conn_fd;
}

void ServerSocket::close() {
    ::close(listen_fd);
}
ServerSocket::~ServerSocket() {
    close();
}