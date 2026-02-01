#pragma once

#include <sys/socket.h>

typedef int (*meth_t)(int const, struct sockaddr const*, 
  socklen_t const);

int lib_connect(char const [], char const [], meth_t const);
void lib_close(int const);
ssize_t lib_write(int const, char const*, size_t const);
ssize_t lib_read(int const, char* const, size_t const);
