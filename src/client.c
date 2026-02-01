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
  cstr_deinit(&c->res);
  cstr_deinit(&c->req);
  cstr_deinit(&c->host);
}

void
client_perform(client_t const* c) {
  /*
  Handle::State s { http.req(host, req.meth, req.endp, req.HDR, req.data) };
  while (s.sent < s.req.size()) {
    if (auto const sent { 
      prot.write(s.req.data() + s.sent, s.req.size() - s.sent) }; sent > 0) 
        s.sent += sent;
    else
      return;
  }

  while (!http.hdr(s.swap))
    if (auto const recv { prot.read(s.swap, 1) }; recv < 1)
      return;
  
  http.stripeol(s.swap);
  req.hdr = s.swap;
  s.swap.clear();

  while (true) {
    auto const recv { prot.read(s.swap, 1) };
    if (recv < 1)
      break;
    
    req.cb(s.swap.data());
    s.swap.clear();
  }
  */
}
