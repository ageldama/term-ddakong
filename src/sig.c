/**
 * Unix signal handling utilities
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "sig.h"
#include "config.h"

#include <signal.h>
#include <stdlib.h>

void
signal_trap_norecover (const int signo, void (*handler) (int))
{
  struct sigaction sa_chld;
  sigemptyset (&sa_chld.sa_mask);
  sa_chld.sa_flags = 0;
  sa_chld.sa_handler = handler;
  sigaction (signo, &sa_chld, NULL);
}
