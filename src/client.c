#include <stdio.h>

#include "lib.h"
#include "proto.h"

#include "client.h"

static int
client_meth(int const fd, struct sockaddr const* addr, 
  socklen_t const len) {
  return connect(fd, addr, len);
}

client_t
client_connect(char const HOST[], char const PORT[]) {
  cstr_t host = cstr_init(HOST);
  return (client_t) {
    .fd = lib_connect(HOST, PORT, client_meth),
    .host = host,
  };
}

void
client_disconn(client_t* const c) {
  lib_close(c->fd);
  cstr_deinit(&c->res);
  cstr_deinit(&c->req);
  cstr_deinit(&c->host);
}

void
client_perform(client_t const* c) {
  cstr_t endp = cstr_init("/");
  cstr_t const hdr[] = {
    cstr_init("Connection: Close"),
  };

  cstr_t req = proto_req(&c->host, proto_GET, 
    &endp, hdr, 1, NULL);
  fprintf(stdout, "%s\n", cstr_data(&req));

  size_t pending = cstr_len(&req);
  while (pending) {
    ssize_t const w =
      lib_write(c->fd, cstr_data(&req), pending);
    pending -= w;
  }

  cstr_t res = cstr_init(NULL);
  char P[128];
  while (1) {
    ssize_t const r = lib_read(c->fd, P, sizeof P);
    if (r > 0) {
      cstr_app(&res, P);
    } else if (r < 1) {
      break;
    }
  }

  fprintf(stdout, "%s\n", cstr_data(&res));
  cstr_deinit(&endp);
  cstr_deinit(&req);
}
