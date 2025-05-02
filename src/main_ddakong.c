
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cc_nanny.h"
#include "fd_io.h"
#include "global_flags.h"
#include "hangeul.h"
#include "im_handler.h"
#include "im_handler_hangeul.h"
#include "pty_.h"
#include "sig.h"
#include "termios_.h"
#include "typedef_.h"
#include "winsz.h"

/* globals */

int child_fd = -1;
pid_t child_pid = 0;

/* internals */

void _exit_cleanup (void);

void trap_chld (const int signo UNUSED);

void trap_winch (int sig_no UNUSED);

void handle_stdin_written (const ssize_t n_written, const BYTE *buf,
                           void *aux);

void
_exit_cleanup (void)
{
  termios__reset ();
  kill_forkpty (child_pid, child_fd);
}

void
trap_chld (const int signo UNUSED)
{
  pid_t pid;
  int status, exitcode;

  while (1)
    {
      pid = waitpid (-1, &status, WNOHANG);
      if (pid <= 0)
        break;
    }
  exitcode = WEXITSTATUS (status);

  if (verbose_flag)
    {
      fprintf (stderr, "# child exited, code:%d\n", exitcode);
    }
  exit (exitcode);
}

void
trap_winch (int sig_no UNUSED)
{
  winsz_update (child_fd);
}

void
handle_stdin_written (const ssize_t n_written, const BYTE *buf, void *aux)
{
  if (aux != NULL)
    {
      FILE *fp = (FILE *)aux;

      if (n_written > 0)
        {
          fwrite (buf, (size_t)n_written, 1, fp);
          fflush (fp);
        }
    }
}

int
main (int argc, char **argv)
{
  do_getopt (argc, argv);

  /* start */
  hangeul_clear_automata_status (&_hangeul_avtomat);

  /* key-logging output */
  FILE *fp = NULL;

  if (keylog_filename != NULL)
    {
      fp = fopen (keylog_filename, "w+");
      if (NULL == fp)
        {
          const ssize_t errmsg_len = 512;
          char errmsg[errmsg_len];
          snprintf (errmsg, errmsg_len, "open(%s) as 'w+' fail",
                    keylog_filename);
          perror (errmsg);
          exit (EXIT_FAILURE);
        }
    }

  /* forpty + exec */
  child_pid = forkpty_with_exec (&child_fd);
  atexit (_exit_cleanup);
  if (verbose_flag)
    {
      fprintf (stderr, "# started child pid: %d\n", child_pid);
    }

  /* signal traps: child-exit, window-change */
  signal_trap_norecover (SIGCHLD, &trap_chld);
  signal_trap_norecover (SIGWINCH, &trap_winch);

  /* terminal size, echo, control-keys */
  winsz_update (child_fd);
  termios__init (0);

  /* fd non-blocking */
  if (-1 == fcntl_nb (STDIN_FILENO, NULL))
    {
      perror ("fcntl_nb(stdin)");
      exit (EXIT_FAILURE);
    }

  if (-1 == fcntl_nb (child_fd, NULL))
    {
      perror ("fcntl_nb(child_fd)");
      exit (EXIT_FAILURE);
    }

  /* epoll: prepare */
  int epollfd = epoll_create1 (0 /* flags */);
  if (epollfd == -1)
    {
      perror ("epoll_create1");
      exit (EXIT_FAILURE);
    }

  if (epoll__add (epollfd, STDIN_FILENO) == -1)
    {
      perror ("epoll_ctl: stdin");
      exit (EXIT_FAILURE);
    }

  if (epoll__add (epollfd, child_fd) == -1)
    {
      perror ("epoll_ctl: child_fd");
      exit (EXIT_FAILURE);
    }

  const int MAX_EVENTS = 10;
  struct epoll_event events[MAX_EVENTS];

  /* prepare: mainloop */
  const int epoll_timeout_ms = 1000;

  const ssize_t buf_max = 1024;
  char buf[buf_max];

  im_handler_status im_hdlr_st;
  im_handler_status__empty (&im_hdlr_st);

  /* mainloop */
  while (1)
    {
      int nfds = epoll_wait (epollfd, events, MAX_EVENTS, epoll_timeout_ms);
      if (nfds == -1)
        {
          perror ("epoll_wait");
          exit (EXIT_FAILURE);
        }

      for (int n = 0; n < nfds; ++n)
        {
          int fd = events[n].data.fd;

          if (child_fd == fd)
            {
              cp_fd (child_fd, STDOUT_FILENO, buf, buf_max);
            }
          else if (STDIN_FILENO == fd)
            {
              handle_stdin (&im_hdlr_st, STDIN_FILENO /* fd_keyin */,
                            child_fd /* fd_child */, buf, buf_max,
                            handle_stdin_written /* write_cb */,
                            (void *)fp /* write_cb_aux */
              );
            }
        }
    }

  exit (EXIT_SUCCESS);
}
