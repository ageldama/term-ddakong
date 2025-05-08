/**
 * "poll-fd" portable file-descriptor polling abstration
 *
 * select(2) implementation
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#include "cc_nanny.h"

const char *
pollfd_impl_name (void)
{
  return "select";
}

pollfd_t *
pollfd_new (const size_t max_evts UNUSED, const int timeout_millis)
{
  assert (max_evts > 0);

  pollfd_t *p = malloc (sizeof (pollfd_t));
  assert (p != NULL);
  memset (p, 0, sizeof (pollfd_t));

  p->_timeout_millis = timeout_millis;
  p->tv_timeout.tv_sec = timeout_millis / 1000;

  p->rfds = NULL;
  p->rfds_len = 0;

  p->wfds = NULL;
  p->wfds_len = 0;

  return p;
}

void
pollfd_free (pollfd_t *p_pollfd)
{
  assert (p_pollfd != NULL);

  if (p_pollfd->rfds != NULL)
    {
      free (p_pollfd->rfds);
    }

  if (p_pollfd->wfds != NULL)
    {
      free (p_pollfd->wfds);
    }

  free (p_pollfd);
}

int *
_add_to_fds (int *fds, int *pinout_fds_len, const int fd)
{
  assert (pinout_fds_len != NULL);

  int *fds_ = fds;

  if (fds_ == NULL)
    {
      fds_ = malloc (sizeof (int));
      fds_[0] = fd;
      *pinout_fds_len = 1;
    }
  else
    {
      (*pinout_fds_len)++;
      fds_ = reallocarray (fds_, (size_t)*pinout_fds_len, sizeof (int));
      assert (fds_ != NULL);
      fds_[*pinout_fds_len - 1] = fd;
    }

  return fds_;
}

int
pollfd_add (pollfd_t *p_pollfd, const int fd, const pollfd_evt_type evt_type)
{
  assert (p_pollfd != NULL);

  switch (evt_type)
    {
    case pollfd_evt_in:
      p_pollfd->rfds = _add_to_fds (p_pollfd->rfds, &(p_pollfd->rfds_len), fd);
      break;

    case pollfd_evt_out:
      p_pollfd->wfds = _add_to_fds (p_pollfd->wfds, &(p_pollfd->wfds_len), fd);
      break;

    default:
      assert ("WTF-evt_type" == NULL);
    }

  return 0;
}

int
_fd_set (fd_set *p_fd_set, int *fds, int fds_len, int max_fd)
{
  int max_fd_ = max_fd;

  for (int i = 0; i < fds_len; i++)
    {
      int fd = fds[i];
      FD_SET (fd, p_fd_set);
      if (max_fd_ < fd)
        max_fd_ = fd;
    }

  return max_fd_;
}

void
_fd_isset (fd_set *p_fd_set, int *fds_in, int fds_in_len, int *fds_out,
           int fds_out_len, int *pinout_cur_pos)
{
  if ((*pinout_cur_pos) + 1 >= (int)fds_out_len)
    {
      return;
    }

  for (int i = 0; i < fds_in_len; i++)
    {
      int fd = (fds_in)[i];
      if (FD_ISSET (fd, p_fd_set))
        {
          if (((*pinout_cur_pos) + 1) <= (int)fds_out_len)
            {
              fds_out[(*pinout_cur_pos)] = fd;
              (*pinout_cur_pos)++;
            }
          else
            return;
        }
    }
}

int
pollfd_wait (pollfd_t *p_pollfd, int *fds UNUSED, const size_t fds_len UNUSED)
{
  assert (p_pollfd != NULL);

  fd_set rfds;
  fd_set wfds;
  int max_fd = 0;

  max_fd = _fd_set (&rfds, p_pollfd->rfds, p_pollfd->rfds_len, max_fd);

  max_fd = _fd_set (&wfds, p_pollfd->wfds, p_pollfd->wfds_len, max_fd);

  int n_select
      = select (max_fd + 1, &rfds, &wfds, NULL, &(p_pollfd->tv_timeout));

  if (n_select == -1)
    {
      perror ("select");
      return n_select;
    }

  int cur_pos UNUSED = 0;

  _fd_isset (&rfds, p_pollfd->rfds, p_pollfd->rfds_len, fds, (int)fds_len,
             &cur_pos);

  _fd_isset (&wfds, p_pollfd->wfds, p_pollfd->wfds_len, fds, (int)fds_len,
             &cur_pos);

  return n_select;
}
