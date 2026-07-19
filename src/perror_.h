/**
 * perror() utilities
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2026. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */
#ifndef perror__h
#define perror__h 1


#ifndef perror_exit
#define perror_exit(msg, exit_code)                                \
  {                                                                \
    perror(msg);                                                   \
    exit(exit_code);                                               \
  }
#endif


#ifndef perror_exit_bad
#define perror_exit_bad(msg) perror_exit(msg, EXIT_FAILURE)
#endif


#endif /* ! perror__h */
