/**
 * termios "window-size" + pty-child process
 *
 * copyright 2025 <ageldama@gmail.com>, 2025. all rights reserved. use
 * of this source code is governed by a gplv3 license that can be
 * found in the license file.
 */

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
