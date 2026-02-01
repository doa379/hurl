#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>

#include "lib.h"

static int
lib_nbio_set(int const fd) {
  return fcntl(fd, F_SETFL, 
    fcntl(fd, F_GETFL, 0) | O_NONBLOCK);
}

int
lib_connect(char const HOST[], char const PORT[],
meth_t const meth) {
  /* Init hints */
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  struct addrinfo* res;
  if (getaddrinfo(HOST, PORT, &hints, &res) == 0) {
    for (struct addrinfo* rp = res; rp; rp = rp->ai_next) {
      int const fd = socket(rp->ai_family, rp->ai_socktype, 
        rp->ai_protocol);
      if (fd != -1) {
        if (meth(fd, rp->ai_addr, rp->ai_addrlen) == 0 &&
            lib_nbio_set(fd) == 0) {
          freeaddrinfo(res);
          return fd;
        }

        close(fd);
      }
    }
    
    freeaddrinfo(res);
  }

  return -1;
}

void
lib_close(int const fd) {
  close(fd);
}

int
lib_poll_in(int const fd, int const toms) {
  struct pollfd pfd = {
    .fd = fd,
    .events = POLLIN,
  };

  return poll(&pfd, 1, toms) > 0 && 
    (pfd.revents & POLLIN) ? 0 : -1;
}

int
lib_poll_out(int const fd, int const toms) {
  struct pollfd pfd = {
    .fd = fd,
    .events = POLLOUT,
  };

  return poll(&pfd, 1, toms) > 0 && 
    (pfd.revents & POLLOUT) ? 0 : -1;
}

int
lib_poll_err(int const fd, int const toms) {
  struct pollfd pfd = {
    .fd = fd,
    .events = POLLHUP | POLLERR | POLLNVAL,
  };

  return poll(&pfd, 1, toms) > 0 && 
    (pfd.revents & (POLLHUP | POLLERR | POLLNVAL)) ? 0 : -1;
}

ssize_t
lib_write(int const fd, char const* p, size_t const n) {
  size_t r = 0;
  while (r < n) {
    ssize_t const R = write(fd, p + r, n - r);
    if (R > 0) {
      r += R;
    } else if (R == 0 || lib_poll_err(fd, 10)) {
      return -1;
    }
  }
  
  return r;
}

ssize_t
lib_read(int const fd, char* const s, size_t const n) {
  char P[128];
  size_t r = 0;
  while (r < n) {
    size_t const d = n - r;
    ssize_t const R =
      read(fd, P, d < sizeof P ? d : sizeof P);
    if (R > 0) {
      memcpy(s + r, P, R);
      r += R;
    } else if (R == 0 || lib_poll_err(fd, 10)) {
      return -1;
    }
  }
  
  return r;
}
