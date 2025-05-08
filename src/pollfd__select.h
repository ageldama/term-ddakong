/**
 * "poll-fd" portable file-descriptor polling abstration
 *
 * select(2) implementation
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef pollfd__select_h
#define pollfd__select_h 1

#include "config.h"
#include "extern_.h"

#include <stddef.h>
#include <stdint.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
  int _timeout_millis;

  struct timeval tv_timeout;

  int *rfds;
  int rfds_len;

  int *wfds;
  int wfds_len;
} pollfd_t;

#endif /* ! pollfd__select_h */
