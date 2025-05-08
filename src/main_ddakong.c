/**
 * ddakong main
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "config.h"

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cc_nanny.h"
#include "fd_io.h"
#include "global_flags.h"
#include "hangeul.h"
#include "im_handler.h"
#include "im_handler_hangeul.h"
#include "plugin.h"
#include "pty_.h"
#include "sig.h"
#include "termios_.h"
#include "typedef_.h"
#include "winsz.h"
#include "pollfd.h"


/* globals */

int child_fd = -1;
pid_t child_pid = 0;
pollfd_t *p_pollfd = NULL;
dll_plugin_context_t dll_plugin_ctx;

/* internals */

/**
 * exit()-종료시 deinit (atexit())
 *
 * @see exit()
 *
 * @see atexit()
 *
 * @see termios__reset()
 *
 * @see kill_forkpty()
 *
 * 1) pty-fd, exec-process 정리
 *
 * 2) termios 상태 복구
 */
void _exit_cleanup (void);

/**
 * 자식프로세스 종료시그널 처리
 *
 * forkpty()/exec() 프로세스가 종료된 것이므로, ddakong도
 * 정리/종료처리.
 *
 * @see forkpty()
 *
 * @see execlp()
 *
 * @see waitpid()
 *
 * @see exit()
 */
void trap_chld (const int signo UNUSED);

/**
 * termios window-size-change 처리
 *
 * 하위-pty에 터미널크기 변동을 반영해줌.
 *
 * @see signal()
 *
 * @see winsz_update()
 */
void trap_winch (int sig_no UNUSED);

/**
 * SIGTERM(kill) 종료처리
 *
 * atexit 핸들러 동작하도록 연결.
 *
 * @see _exit_cleanup
 *
 * @see exit
 */
void trap_term (int sig_no);

/**
 * stdin 입력을 처리한 다음 호출되는 콜백함수
 *
 * key-logging 파일에 기록.
 */
void handle_stdin_written (const ssize_t n_written, const BYTE *buf,
                           void *aux);

void
_exit_cleanup (void)
{
  if (verbose_flag)
    {
      fprintf (stderr, "# cleanup on exiting...\n");
    }

  termios__reset ();
  kill_forkpty (child_pid, child_fd);

  if (dll_plugin_ctx.p_dll != NULL)
    {
      dll_plugin_unload (&dll_plugin_ctx);
    }

  if (p_pollfd != NULL)
    {
      pollfd_free(p_pollfd);
    }
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
trap_term (int sig_no)
{
  if (verbose_flag)
    {
      fprintf (stderr, "# trapped (%d) : exiting\n", sig_no);
    }

  exit (EXIT_FAILURE);
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
  /* 기본 입력핸들러를 위한 상태 */
  im_handler_status default_im_hndlr_st;
  im_handler_status__empty (&default_im_hndlr_st);

  set_current_handle_input_status (&default_im_hndlr_st);
  set_current_handle_input_fn ((handle_input_fn_t)handle_stdin);

  hangeul_clear_automata_status (&_hangeul_avtomat);

  /* getopt: 커맨드라인 파라미터 처리 */
  do_getopt (argc, argv);

  if (verbose_flag)
    {
      print_banner (stderr);
    }

  /* dll-plugin: 초기화 */
  dll_plugin_ctx.p_dll = NULL;

  if (NULL != plugin_dll_filename)
    {
      BOOL dll_plugin_loaded
          = dll_plugin_load (&dll_plugin_ctx, plugin_dll_filename);
      if (verbose_flag)
        {
          fprintf (stderr, "# dll-plugin loaded?(%d)\n", dll_plugin_loaded);
        }
    }

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
  signal_trap_norecover (SIGTERM, &trap_term);

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

  /* pollfd: prepare */
  const int MAX_EVTS = 10;
  const int EVT_TIMEOUT_MILLIS = 1000;

  if (verbose_flag)
    {
      fprintf(stderr, "# pollfd(%s)\n",
              pollfd_impl_name());
    }

  p_pollfd = pollfd_new (MAX_EVTS, EVT_TIMEOUT_MILLIS);
  if (p_pollfd == NULL)
    {
      exit (EXIT_FAILURE);
    }

  if(-1 == pollfd_add(p_pollfd,
                      STDIN_FILENO,
                      pollfd_evt_in))
    {
      perror ("epoll_ctl: stdin");
      exit (EXIT_FAILURE);
    }

  if (-1 == pollfd_add(p_pollfd,
                       child_fd,
                       pollfd_evt_in))
    {
      perror ("epoll_ctl: child_fd");
      exit (EXIT_FAILURE);
    }


  /* prepare: mainloop */
  const ssize_t buf_max = 1024;
  char buf[buf_max];

  /* mainloop */
  handle_input_fn_t handle_input = get_current_handle_input_fn ();
  void *p_handle_input_status = get_current_handle_input_status ();

  int fds[MAX_EVTS];

  while (1)
    {
      int nfds = pollfd_wait (p_pollfd, fds, MAX_EVTS);
      if (nfds == -1)
        {
          continue;
        }

      for (int n = 0; n < nfds; ++n)
        {
          int fd = fds[n];

          if (child_fd == fd)
            {
              cp_fd (child_fd, STDOUT_FILENO, buf, buf_max);
            }
          else if (STDIN_FILENO == fd)
            {
              handle_input (p_handle_input_status, STDIN_FILENO /* fd_keyin */,
                            child_fd /* fd_child */, buf, buf_max,
                            handle_stdin_written /* write_cb */,
                            (void *)fp /* write_cb_aux */
              );
            }
        }
    }

  exit (EXIT_SUCCESS);
}
