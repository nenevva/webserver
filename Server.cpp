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

#include "Server.h"
#include "ThreadPool.h"

using namespace std;

Server::Server(int port) : serverSocket(port)
{
    serverSocket.bind();
    serverSocket.listen();
}
char *Server::job(int conn_fd, char *buf, int msglen)
{
    cout << buf << endl;
    char* str = "hello";
    return str;
}

void Server::run()
{
    ThreadPool threadPool(10);
    int epoll_fd = epoll_create(1024);
    int listen_fd = serverSocket.listen_fd;
    epoll_event rdlist[1024];
    epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event);
    cout << "server is running, waiting for connection" << endl;
    while (1)
    {
        cout << "waiting" << endl;
        int rd_num = epoll_wait(epoll_fd, rdlist, 1024, -1);
        cout << "rd_num: " << rd_num << endl;
        for (int i = 0; i < rd_num; i++)
        {
            if (rdlist[i].data.fd == listen_fd)
            {
                cout << "new connection\n"
                     << endl;
                int conn_fd = serverSocket.accept();
                epoll_event event;
                event.events = EPOLLIN;
                event.data.fd = conn_fd;
                int ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &event);
                cout << "add new connection: " << ret << endl;
            }
            else
            {
                cout << "data incoming" << endl;
                int conn_fd = rdlist[i].data.fd;
                char buf[2048];
                int msglen = read(conn_fd, buf, 2048);
                if (msglen <= 0)
                {
                    cout << "delete connection" << endl;
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, conn_fd, NULL);
                }
                else
                {
                    auto result = threadPool.enqueue(job, conn_fd, buf, msglen);
                    write(conn_fd, result.get(), msglen);
                }
            }
        }
    }
    close(listen_fd);
    close(epoll_fd);
}