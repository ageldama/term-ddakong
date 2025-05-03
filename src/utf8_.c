/**
 * UTF-8 + Unicode 변환
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "utf8_.h"

int
unicode_to_utf8 (const UNICODE_32 code, BYTE *buf)
{
  if (code <= 0x7f)
    {
      // ascii
      buf[0] = (BYTE)code;
      return 1;
    }
  else if (code <= 0x07ff)
    {
      buf[0] = (BYTE)(((code >> 6) & 0x1f) | 0xc0);
      buf[1] = (BYTE)(((code >> 0) & 0x3f) | 0x80);
      return 2;
    }
  else if (code <= 0xffff)
    {
      buf[0] = (BYTE)(((code >> 12) & 0x0f) | 0xe0);
      buf[1] = (BYTE)(((code >> 6) & 0x3f) | 0x80);
      buf[2] = (BYTE)(((code >> 0) & 0x3f) | 0x80);
      return 3;
    }
  else if (code <= 0x10ffff)
    {
      buf[0] = (BYTE)(((code >> 18) & 0x07) | 0xf0);
      buf[1] = (BYTE)(((code >> 12) & 0x3f) | 0x80);
      buf[2] = (BYTE)(((code >> 6) & 0x3f) | 0x80);
      buf[3] = (BYTE)(((code >> 0) & 0x3f) | 0x80);
      return 4;
    }
  else
    {
      // fallback : "�" / unicode = 65533.
      buf[0] = (BYTE)0xef;
      buf[1] = (BYTE)0xbf;
      buf[2] = (BYTE)0xbd;
      return 0;
    }
}
