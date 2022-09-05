#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/socket.h>

#include "Util.h"

using namespace std;

void setReusePort(int fd)
{
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
}

int setNonBlocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}