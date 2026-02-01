#include <stdlib.h>
#include <string.h>

#include "cstr.h"

static size_t RES = sizeof ((cstr_t*) 0)->s;

cstr_t
cstr_init(char const* str) {
  cstr_t cstr = {
    .len = strlen(str),
    .res = RES,
  };
  
  if (cstr.len < RES) {
    memcpy(cstr.s, str, cstr.len);        
    cstr.s[cstr.len] = '\0';
  } else {
    cstr.p = malloc(cstr.len + 1);
    if (cstr.p) {
      memcpy(cstr.p, str, cstr.len);
      cstr.p[cstr.len] = '\0';
      cstr.res = cstr.len + 1;
    }
  }

  return cstr;
}

void
cstr_app(cstr_t* const cstr, char const* str) {
  size_t const l = strlen(str);
  size_t const nextl = cstr->len + l;

  if (nextl < RES) {
    strncat(cstr->s, str, l);
    cstr->s[nextl] = '\0';
    cstr->len = nextl;
  } else if (cstr->res < RES) {
    char* buf = malloc(nextl + 1);
    if (buf) {
      memcpy(buf, cstr->s, cstr->len);
      memcpy(buf + cstr->len, str, l);
      cstr->p = buf;
      cstr->len = nextl;
      cstr->res = nextl + 1;
    }
  } else {
    cstr->p = realloc(cstr->p, nextl + 1);
    if (cstr->p) {
      memcpy(cstr->p + cstr->len, str, l);
      cstr->len = nextl;
      cstr->res = nextl + 1;
    }
  }
}

void
cstr_deinit(cstr_t* const cstr) {
  if (cstr->res > RES) {
    free(cstr->p);
  }
}

char const*
cstr_data(cstr_t const* cstr) {
  return cstr->res > RES ? cstr->p : cstr->s;
}

size_t
cstr_len(cstr_t const* cstr) {
  return cstr->len;
}
