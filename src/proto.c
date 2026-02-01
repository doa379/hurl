#include <stdio.h>

#include "proto.h"

static char const* METH[] = {
  "GET", 
  "PUT", 
  "POST", 
  "DELETE", 
  "PATCH",
  "HEAD",
  "OPTIONS",
  "CONNECT",
  "TRACE"
};

static char const USER[] = "Request";

cstr_t
proto_req(cstr_t const* host, enum proto_meth const m, 
cstr_t const* endp, cstr_t const* hdr[], unsigned const nhdr, 
cstr_t const* data) {
  cstr_t req;
  cstr_app(&req, METH[m]);
  cstr_app(&req, " ");
  cstr_app(&req, cstr_data(endp));
  cstr_app(&req, " HTTP/1.1\r\n");
  cstr_app(&req, "Host: ");
  cstr_app(&req, cstr_data(host));
  cstr_app(&req, "\r\n");
  cstr_app(&req, "User-Agent: ");
  cstr_app(&req, USER);
  cstr_app(&req, "\r\n");
  cstr_app(&req, "Accept: */*\r\n");
  for (unsigned i = 0; i < nhdr; i++) {
    cstr_app(&req, cstr_data(hdr[i]));
    cstr_app(&req, "\r\n");
  }

  size_t const len = cstr_len(data);
  if (len) {
    cstr_app(&req, "Content-Length: ");
    /* convert to alpha */
    char len_s[24];
    snprintf(len_s, sizeof len_s, "%zu", len);
    cstr_app(&req, len_s);
    cstr_app(&req, "\r\n\r\n");
    cstr_app(&req, cstr_data(data));
  }

  cstr_app(&req, "\r\n");
  return req;
}
