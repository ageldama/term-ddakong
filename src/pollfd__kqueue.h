/**
 * "poll-fd" portable file-descriptor polling abstration
 *
 * kqueue implementation
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef pollfd__kqueue_h
#define pollfd__kqueue_h 1

#include "config.h"

#include "extern_.h"

#include <stddef.h>
#include <stdint.h>

#ifdef HAVE_SYS_EVENT_H
#include <sys/event.h>
#endif

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif


typedef struct
{
  size_t max_evts;

  int timeout_millis;
  struct timespec timeout;

  int kq;
  struct kevent evt_change;
  struct kevent *evt_triggered;
} pollfd_t;

#endif /* ! pollfd__kqueue_h */
