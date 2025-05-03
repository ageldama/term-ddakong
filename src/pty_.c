/**
 * forkpty() utilities
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */
#include "pty_.h"

#include <fcntl.h>
#include <pty.h>
#include <signal.h>
#include <stddef.h> // for size_t
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t
forkpty_with_exec (int *fd_amaster)
{
  pid_t pid;

  pid = forkpty (fd_amaster, NULL, NULL, NULL);
  if (!pid)
    {
      char *sz_shell = getenv ("SHELL");
      if (NULL == sz_shell)
        {
          sz_shell = "/bin/sh";
        }
      execlp (sz_shell, sz_shell, NULL);
    }

  /* NOTE fd_io 모듈에 있는 함수지만, 또 어차피 main()-에서 이미
     처리해주지만, 그냥 둘까 */
  fcntl (*fd_amaster, F_SETFL, fcntl (*fd_amaster, F_GETFL) | O_NONBLOCK);

  return pid;
}

void
kill_forkpty (pid_t pid, int fd)
{
  kill (pid, SIGTERM);
  close (fd);
  waitpid (pid, NULL, 0);
}
