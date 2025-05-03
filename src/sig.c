/**
 * Unix signal handling utilities
 *
 * copyright 2025 <ageldama@gmail.com>, 2025. all rights reserved. use
 * of this source code is governed by a gplv3 license that can be
 * found in the license file.
 */

#include "sig.h"

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
