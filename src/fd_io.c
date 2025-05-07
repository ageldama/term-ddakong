/**
 * Utilities for "Unix file-descriptor"
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "fd_io.h"

#include <fcntl.h>      /* for fcntl, F_GETFL, F_SETFL, O_NONBLOCK */
#include <stddef.h>     /* for size_t, NULL */
#include <sys/epoll.h>  /* for epoll_event, epoll_ctl, EPOLLIN, EPOLL_CTL_ADD */
#include <unistd.h>     /* for read, write */

ssize_t
cp_fd (const int src_fd, const int dst_fd, char *buf, const ssize_t buf_max)
{
  ssize_t n_read = read (src_fd, buf, (size_t)buf_max);
  if (n_read < 0)
    return n_read;

  ssize_t n_written = 0;
  if (n_read > 0)
    {
      n_written = write (dst_fd, buf, (size_t)n_read);
    }
  return n_written;
}

int
fcntl_nb (const int fd, int *p_old_fl)
{
  int old_fl = fcntl (fd, F_GETFL);
  if (old_fl == -1)
    {
      return -1; // error
    }

  if (p_old_fl != NULL)
    {
      *p_old_fl = old_fl;
    }

  return fcntl (fd, F_SETFL, old_fl | O_NONBLOCK);
}

int
epoll__add (const int epollfd, const int fd)
{
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = fd;
  return epoll_ctl (epollfd, EPOLL_CTL_ADD, fd, &ev);
}
