#ifndef sig_h
#define sig_h 1

#include <sys/types.h>

#include "extern_.h"

EXTERN_ void signal_trap_norecover (const int signo, void (*) (int));

#endif /* ! sig_h */
