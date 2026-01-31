#include "lib.h"

static int const LISTEN_QLEN = 16;

static int
srv_meth(int const fd, struct sockaddr const* addr, 
  socklen_t const len) {
  return bind(fd, addr, len) == 0 &&
    listen(fd, LISTEN_QLEN) == 0 ? 0 : -1;
}

int
server_connect(char const PORT[]) {
  return lib_connect("0.0.0.0", PORT, srv_meth);
}

