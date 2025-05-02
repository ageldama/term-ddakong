#ifndef sig_h
#define sig_h 1

#include "extern_.h"

#include <sys/types.h>

EXTERN_ void signal_trap_norecover (const int signo, void (*) (int));

#endif /* ! sig_h */
