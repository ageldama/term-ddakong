#ifndef pollfd__select_h
#define pollfd__select_h 1


#include "config.h"
#include "extern_.h"

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>


typedef struct {
  int _timeout_millis;

  struct timeval tv_timeout;

  int *rfds;
  int rfds_len;

  int *wfds;
  int wfds_len;
} pollfd_t;



#endif /* ! pollfd__select_h */
