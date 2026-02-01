#pragma once

typedef struct {
  int fd;
  cstr_t host;
  cstr_t req;
  cstr_t res;
} client_t;

client_t client_connect(char const[], char const[]);
void client_disconn(client_t* const);
void client_perform(client_t const*);

