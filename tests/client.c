#include <stdio.h>

#include "../src/client.h"

static char const VAL[] = "example.com";
static char const INVAL[] = "eeeeeeeeeeeeeeeeeeeeeeeeeeeee.com";

int main() {
  {
    client_t const c = client_connect(VAL, "80");
    fprintf(stdout, "Connection result %d\n", c.fd);
    client_perform(&c);
  }

  {
    client_t const c = client_connect(INVAL, "80");
    fprintf(stdout, "Connection result %d\n", c.fd);
    client_perform(&c);
  }

  return 0;
}
