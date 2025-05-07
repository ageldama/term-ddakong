#ifndef pollfd_h /* I know this is terrible naming */
#define pollfd_h 1

#include "extern_.h"

#include "config.h"

#include <stdint.h>


#ifdef HAVE_SYS_EPOLL_H /* Linux/epoll */
#include "pollfd__linux_epoll.h"
#endif /* HAVE_SYS_EPOLL_H */



EXTERN_
pollfd_t *pollfd_new(const size_t max_evts,
                     const int timeout_millis);

EXTERN_
void pollfd_free(pollfd_t *p_pollfd);


EXTERN_
int pollfd_add(pollfd_t *p_pollfd,
               const int fd,
               const uint32_t evt_type);


EXTERN_
int pollfd_wait(pollfd_t *p_pollfd,
                int *fds, const size_t fds_len);






#endif /* ! pollfd_h */
