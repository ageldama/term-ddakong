/**
 * termios "window-size" + pty-child process
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
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
