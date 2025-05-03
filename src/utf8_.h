/**
 * UTF-8 + Unicode 변환
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef utf8__h
#define utf8__h 1

#include <stdint.h>

#include "typedef_.h"

/**
 * Convert Unicode code point into UTF-8 bytes
 *
 * @param code unicode code point.
 * @param buf minimum 4-bytes. (not zero terminated)
 * @return 0 = error, number of utf-8 bytes copied to `buf`.
 */
int unicode_to_utf8 (const UNICODE_32 code, BYTE *buf);

#endif /* ! utf8__h */
