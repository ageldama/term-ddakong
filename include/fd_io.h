#ifndef fd_io_h
#define fd_io_h 1

#include <sys/types.h>

#include "extern_.h"

EXTERN_ ssize_t cp_fd (const int src_fd, const int dst_fd, char *buf,
                       const ssize_t buf_max);

EXTERN_ int fcntl_nb (const int fd, int *p_old_fl);

EXTERN_
int epoll__add (const int epollfd, const int fd);

#endif /* ! fd_io_h */
