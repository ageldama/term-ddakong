#include "pollfd.h"



#ifdef HAVE_SYS_EPOLL_H
#include "pollfd__linux_epoll.c"
#endif /* HAVE_SYS_EPOLL_H */
