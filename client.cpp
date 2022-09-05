#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

int main()
{

    printf("client started\n");

    // create socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == clientfd)
    {
        printf("create socket error");
        return -1;
    }

    // connect server
    struct sockaddr_in serveraddr{};
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ;
    serveraddr.sin_port = htons(8088);

    if (-1 == connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)))
    {
        printf("connect error");
        return -1;
    }

    int i = 100;
    while (i--)
    {
        // send data
        printf("sending\n");
        int ret = send(clientfd, "hello", strlen("hello"), 0);
        if (ret != strlen("hello"))
        {
            printf("send data error");
            return -1;
        }

        // receive data
        char recvBuf[32] = {0};
        ret = recv(clientfd, recvBuf, 32, 0);
        if (ret > 0)
        {
            printf("receive data from server: %s\n", recvBuf);
        }
        else
        {
            printf("receive data error: %s", recvBuf);
        }
        sleep(1);
    }

    // close socket
    close(clientfd);

    return 0;
}