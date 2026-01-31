#pragma once

#include <sys/socket.h>

typedef int (*meth_t)(int const, struct sockaddr const*, socklen_t const);

void lib_init();
int lib_connect(char const [], char const [], meth_t const);
