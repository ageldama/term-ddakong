/**
 * "poll-fd" portable file-descriptor polling abstration
 *
 * kqueue implementation
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "cc_nanny.h"
#include "config.h"
#include "pollfd.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *
pollfd_impl_name (void)
{
  return "kqueue";
}

pollfd_t *
pollfd_new (const size_t max_evts, const int timeout_millis)
{
  assert (max_evts > 0);

  pollfd_t *p = malloc (sizeof (pollfd_t));
  assert (p != NULL);
  memset (p, 0, sizeof (pollfd_t));

  p->max_evts = max_evts;
  p->timeout_millis = timeout_millis;

  int kq = kqueue ();
  if (-1 == kq)
    {
      perror ("kqueue");
      free (p);
      return NULL;
    }

  p->kq = kq;

  p->evt_triggered = calloc (max_evts, sizeof (struct kevent));
  assert (p->evt_triggered != NULL);

  return p;
}

void
pollfd_free (pollfd_t *p_pollfd)
{
  if (p_pollfd->evt_triggered != NULL)
    {
      free (p_pollfd->evt_triggered);
    }

  if (p_pollfd != NULL)
    {
      if (p_pollfd->kq != 0)
        {
          close (p_pollfd->kq);
        }

      free (p_pollfd);
    }
}

int
pollfd_add (pollfd_t *p_pollfd, const int fd, const pollfd_evt_type evt_type)
{
  assert (p_pollfd != NULL);

  switch (evt_type)
    {
    case pollfd_evt_in:
      EV_SET (&(p_pollfd->evt_change), fd, EVFILT_READ, EV_ADD, 0, 0, 0);
      break;

    case pollfd_evt_out:
      EV_SET (&(p_pollfd->evt_change), fd, EVFILT_WRITE, EV_ADD, 0, 0, 0);
      break;

    default:
      assert ("WTF-evt_type" == NULL);
    }

  if (kevent (p_pollfd->kq, &(p_pollfd->evt_change), 1, NULL, 0, NULL) == -1)
    {
      perror ("kevent(EV_ADD)");
      return -1;
    }
  return 0;
}

int
pollfd_wait (pollfd_t *p_pollfd, int *fds, const size_t fds_len)
{
  assert (p_pollfd != NULL);

  int n_evt = kevent (p_pollfd->kq, NULL, 0, p_pollfd->evt_triggered,
                      (int)p_pollfd->max_evts, NULL);

  if (n_evt < 0)
    {
      perror ("kevent(wait)");
      return n_evt;
    }

  for (int i = 0; i < n_evt; i++)
    {
      if ((int)fds_len < i + 1)
        break;

      int event_fd = (int)p_pollfd->evt_triggered[i].ident;

      fds[i] = event_fd;
    }

  return n_evt;
}
