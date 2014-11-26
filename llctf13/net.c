#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle(int fd);

void
netserv(void)
{
  int srv = socket(AF_INET, SOCK_STREAM, 0);
  assert(srv >= 0);

  int reuse = 1;
  assert(setsockopt(srv, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) >= 0);

  struct sockaddr_in sin = { .sin_family = AF_INET,
                             .sin_addr.s_addr = INADDR_ANY,
                             .sin_port = htons(1234) };
  assert(bind(srv, (struct sockaddr*) &sin, sizeof(sin)) >= 0);
  assert(listen(srv, 5) >= 0);

  for (;;) {
    socklen_t len = sizeof(sin);
    int fd = accept(srv, (struct sockaddr*) &sin, &len);
    assert(fd >= 0);
    handle(fd);
    close(fd);
  }
}
