#ifndef pty__h
#define pty__h 1

#include "extern_.h"

#include <sys/types.h>

#ifdef __APPLE__
#include <util.h>
#else
/*#include <pty.h>*/
#endif

EXTERN_ pid_t forkpty_with_exec (int *fd_amaster);

EXTERN_ void kill_forkpty (const pid_t pid, const int fd);

#endif /* ! pty__h */
