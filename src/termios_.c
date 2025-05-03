/**
 * termios init/reset
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "termios_.h"

#include <termios.h>

/**
 * termios__init 이전 상태, 변경후 상태 저장변수. (global, private)
 */
static struct termios _termios_old, _termios_cur;

void
termios__init (int echo)
{
  tcgetattr (0, &_termios_old);
  _termios_cur = _termios_old;

  /* no buffer */

  _termios_cur.c_iflag &= (tcflag_t)~ISTRIP;
  _termios_cur.c_lflag &= (tcflag_t)~ICANON;

  /* echo */
  if (echo)
    {
      _termios_cur.c_lflag |= (tcflag_t)ECHO; /* Y */
    }
  else
    {
      _termios_cur.c_lflag &= (tcflag_t)~ECHO; /* N */
    }

  /* C-c, C-z, C-\ ... => forwarding */
  _termios_cur.c_lflag &= (tcflag_t)~ISIG;

  tcsetattr (0, TCSANOW, &_termios_cur);
}

void
termios__reset (void)
{
  tcsetattr (0, TCSANOW, &_termios_old);
}
