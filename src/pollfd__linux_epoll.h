#ifndef pollfd__linux_epoll_h
#define pollfd__linux_epoll_h 1

#include "config.h"
#include "extern_.h"


#include <stdint.h>
#include <stddef.h>


typedef struct {
  int epollfd;

  struct epoll_event *epoll_evts;
  size_t epoll_evts_len;
  int epoll_timeout_millis;

  int *fds;
  int fds_len;
} pollfd_t;



#include <sys/epoll.h>


EXTERN_
int epoll__create();


EXTERN_
int epoll__wait(int epollfd,
                struct epoll_event *evts,
                const size_t evts_len,
                const int timeout_millis);


/**
 * file-descriptor을 epoll-file-descriptor에 추가하기
 *
 * @param epoll_ctl
 *
 * @param epollfd target epoll-fd
 *
 * @param fd 추가할 file-descriptor
 *
 * @param evt_type epoll event-type for `epoll_ctl' (eg. EPOLLIN)
 *
 * @return epoll_ctl()-함수의 리턴값 그대로.
 */
EXTERN_
int epoll__add (const int epollfd, const int fd,
                const uint32_t evt_type);


EXTERN_
int
epoll__del (const int epollfd, const int fd);



#endif /* pollfd__linux_epoll_h */
