/*
sockpp::Poll::Poll(int const fd)
noexcept : 
pfd { fd }
{ }

void
sockpp::Poll::set_fd(int const fd) 
noexcept { 
  pfd.fd = fd;
}

bool
sockpp::Poll::set_nbio(int const fd)
const noexcept {
  return ::fcntl(fd, F_SETFL, 
    ::fcntl(fd, F_GETFL, 0) | O_NONBLOCK) == 0;
}

int 
sockpp::Poll::fd() 
const noexcept { 
  return pfd.fd;
}

bool
sockpp::Poll::in(int const toms)
noexcept {
  pfd.events = POLLIN;
  return ::poll(&pfd, 1, toms) > 0 && (pfd.revents & POLLIN);
}

bool
sockpp::Poll::out(int const toms)
noexcept {
  pfd.events = POLLOUT;
  return ::poll(&pfd, 1, toms) > 0 && (pfd.revents & POLLOUT);
}

bool
sockpp::Poll::err(int const toms)
noexcept {
  pfd.events = POLLHUP | POLLERR | POLLNVAL;
  return ::poll(&pfd, 1, toms) > 0 && 
    (pfd.revents & (POLLHUP | POLLERR | POLLNVAL));
}
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>

#include "lib.h"

static struct addrinfo hints;
static struct pollfd pfd;

void
lib_init() {
  /* Init hints */
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  /* Init pfd */
  memset(&pfd, 0, sizeof pfd);
}

int
lib_connect(char const HOST[], char const PORT[],
meth_t const meth) {
  lib_init();
  struct addrinfo* res;
  if (getaddrinfo(HOST, PORT, &hints, &res) == 0) {
    for (struct addrinfo* rp = res; rp; rp = rp->ai_next) {
      int const fd = socket(rp->ai_family, rp->ai_socktype, 
        rp->ai_protocol);
      if (fd != -1) {
        
        /*
        if (meth(fd, rp->ai_addr, rp->ai_addrlen) &&
            poll.set_nbio(fd)) {
          poll.set_fd(fd);
          freeaddrinfo(res);
          return 0;
        }
        */
        if (meth(fd, rp->ai_addr, rp->ai_addrlen)) {
          freeaddrinfo(res);
          return 0;
        }

        close(fd);
      }
    }
    
    freeaddrinfo(res);
  }

  return -1;
}
