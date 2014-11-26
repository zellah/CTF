#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int ac, char **av)
{
  size_t total = 0;
  for (;;) {
    size_t itersize = 1024 * 1024;
    char* buf = malloc(itersize);
    if (!buf) {
      printf("Unable to allocate memory\n");
      break;
    }

    memset(buf, 0xab, itersize);
    total += itersize;
    printf("Got %ld bytes of memory\n", total);
  }
}
