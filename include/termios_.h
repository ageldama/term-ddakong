#ifndef termios__h
#define termios__h 1

#include "extern_.h"

EXTERN_ void termios__init (int echo);

EXTERN_ void termios__reset (void);

#endif /* ! termios__h */
