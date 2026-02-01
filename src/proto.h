#pragma once

#include "cstr.h"

enum proto_meth { 
  proto_GET, 
  proto_PUT, 
  proto_POST, 
  proto_DELETE, 
  proto_PATCH,
  proto_HEAD,
  proto_OPTIONS,
  proto_CONNECT,
  proto_TRACE
};

cstr_t
proto_req(cstr_t const*, enum proto_meth const, 
cstr_t const*, cstr_t const* [], unsigned const, 
cstr_t const*);
