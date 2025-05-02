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

  /*
   * int *amster,
   * char *name,
   * const struct termios *termp,
   * const struct winsize *winp
   */
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
