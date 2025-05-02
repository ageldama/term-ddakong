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
