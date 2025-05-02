#include "winsz.h"

#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

void
winsz_update (const int child_fd)
{
  struct winsize winsz;
  ioctl (STDIN_FILENO, TIOCGWINSZ, &winsz);
  ioctl (child_fd, TIOCSWINSZ, &winsz);
}
