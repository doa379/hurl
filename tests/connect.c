#include <stdio.h>

#include "../src/client.h"

static char const VAL[] = "example.com";
static char const INVAL[] = "eeeeeeeeeeeeeeeeeeeeeeeeeeeee.com";

int main() {
  {
    int const res = client_connect(VAL, "80");
    fprintf(stdout, "Result %d\n", res);
  }

  {
    int const res = client_connect(INVAL, "80");
    fprintf(stdout, "Result %d\n", res);
  }

  return 0;
}
