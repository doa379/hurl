#include "lib.h"

static int
client_meth(int const fd, struct sockaddr const* addr, 
  socklen_t const len) {
  return connect(fd, addr, len);
}

int
client_connect(char const HOST[], char const PORT[]) {
  return lib_connect(HOST, PORT, client_meth);
}

