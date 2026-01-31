#include <stdio.h>

#include "../src/client.h"

int main() {
  int const res = client_connect("example.com", "80");
  fprintf(stdout, "Result %d\n", res);
  return 0;
}
