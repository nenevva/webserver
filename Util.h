#pragma once

#include <string>

using namespace std;

void setReusePort(int fd);

int setNonBlocking(int fd);