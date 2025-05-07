#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/epoll.h>  /* for epoll_event, epoll_ctl, EPOLLIN, EPOLL_CTL_ADD */

#include "cc_nanny.h"


int epoll__create()
{
  int epollfd = epoll_create1 (0 /* flags */);
  return epollfd;
}


int epoll__wait(int epollfd,
                struct epoll_event *evts,
                const size_t evts_len,
                const int timeout_millis)
{
  int nfds = epoll_wait (epollfd, evts, (int) evts_len, timeout_millis);
  return nfds;
}


int
epoll__add (const int epollfd, const int fd,
            const uint32_t evt_type)
{
  struct epoll_event ev;
  ev.events = evt_type;
  ev.data.fd = fd;
  return epoll_ctl (epollfd, EPOLL_CTL_ADD, fd, &ev);
}


int
epoll__del (const int epollfd, const int fd)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  return epoll_ctl (epollfd, EPOLL_CTL_DEL, fd, &ev);
}



pollfd_t *pollfd_new(const size_t max_evts,
                     const int timeout_millis)
{
  assert(max_evts > 0);

  pollfd_t *p = malloc(sizeof(pollfd_t));
  assert(p != NULL);
  memset(p, 0, sizeof(pollfd_t));

  p->epoll_evts = calloc
    (max_evts, sizeof(struct epoll_event));
  assert(p->epoll_evts != NULL);

  p->epoll_evts_len = max_evts;
  p->epoll_timeout_millis = timeout_millis;

  p->fds = NULL;
  p->fds_len = 0;

  p->epollfd = epoll__create();
  if (p->epollfd == -1)
    {
      perror("epoll_create1");
      free(p->epoll_evts);
      free(p);
      return NULL;
    }

  return p;
}


void pollfd_free(pollfd_t *p_pollfd)
{
  assert(p_pollfd != NULL);

  for (int i=0; i<p_pollfd->fds_len; i++)
    {
      int fd = p_pollfd->fds[i];
      epoll__del(p_pollfd->epollfd, fd);
    }

  if (p_pollfd->fds != NULL)
    {
      free(p_pollfd->fds);
    }

  close(p_pollfd->epollfd);

  free(p_pollfd->epoll_evts);
  free(p_pollfd);
}


int pollfd_add(pollfd_t *p_pollfd,
               const int fd,
               const pollfd_evt_type evt_type)
{
  assert(p_pollfd != NULL);

  if (p_pollfd->fds == NULL)
    {
      p_pollfd->fds = malloc(sizeof(int));
      p_pollfd->fds[0] = fd;
      p_pollfd->fds_len = 1;
    }
  else
    {
      p_pollfd->fds_len ++;
      p_pollfd->fds =
        reallocarray(p_pollfd->fds,
                     (size_t) p_pollfd->fds_len,
                     sizeof(int));
      assert(p_pollfd->fds != NULL);
      p_pollfd->fds[p_pollfd->fds_len - 1] = fd;
    }

  uint32_t evt_type_ = 0;

  switch (evt_type)
    {
    case pollfd_evt_in:
      evt_type_ = EPOLLIN;
      break;

    case pollfd_evt_out:
      evt_type_ = EPOLLOUT;
      break;

    default:
      assert("WTF-evt_type" == NULL);
    }

  return epoll__add(p_pollfd->epollfd, fd, evt_type_);
}


int pollfd_wait(pollfd_t *p_pollfd,
                int *fds, const size_t fds_len)
{
  assert(p_pollfd != NULL);

  int nfds = epoll__wait(p_pollfd->epollfd,
                         p_pollfd->epoll_evts,
                         p_pollfd->epoll_evts_len,
                         p_pollfd->epoll_timeout_millis);
  if (nfds < 0) return nfds;

  for (int i=0; i < nfds; i++)
    {
      if ((int)fds_len < i+1) break;

      struct epoll_event evt = p_pollfd->epoll_evts[i];
      fds[i] = evt.data.fd;
    }

  return nfds;
}


