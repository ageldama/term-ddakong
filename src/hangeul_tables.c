/**
 * 한글 => 유니코드, 2벌식 자판용 매핑 테이블
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include <stdint.h>
#include <stdlib.h>

#include "hangeul.h"

const BYTE _cho_code_to_2beol_lut[] = {
  'r' /* ㄱ 0 */,  'R' /* ㄲ 1 */,  's' /* ㄴ 2 */,  'e' /* ㄷ 3 */,
  'E' /* ㄸ 4 */,  'f' /* ㄹ 5 */,  'a' /* ㅁ 6 */,  'q' /* ㅂ 7 */,
  'Q' /* ㅃ 8 */,  't' /* ㅅ 9 */,  'T' /* ㅆ 10 */, 'd' /* ㅇ 11 */,
  'w' /* ㅈ 12 */, 'W' /* ㅉ 13 */, 'c' /* ㅊ 14 */, 'z' /* ㅋ 15 */,
  'x' /* ㅌ 16 */, 'v' /* ㅍ 17 */, 'g' /* ㅎ 18 */,
};

const ssize_t _cho_code_to_2beol_lut_len = 19;

const BYTE *_cho_chord_to_2beol_lut[] = {
  NULL /* ( 0 ) ㄱ */,          "rr" /* ( 1 ) ㄱ+ㄱ => ㄲ */,
  NULL /* ( 2 ) ㄴ */,          NULL /* ( 3 ) ㄷ */,
  "ee" /* ( 4 ) ㄷ+ㄷ => ㄸ */, NULL /* ( 5 ) ㄹ */,
  NULL /* ( 6 ) ㅁ */,          NULL /* ( 7 ) ㅂ */,
  "qq" /* ( 8 ) ㅂ+ㅂ => ㅃ */, NULL /* ( 9 ) ㅅ */,
  "tt" /* (10 ) ㅅ+ㅅ => ㅆ */, NULL /* (11 ) ㅇ */,
  NULL /* (12 ) ㅈ */,          "ww" /* (13 ) ㅈ+ㅈ => ㅉ */,
};

const ssize_t _cho_chord_to_2beol_lut_len = 14;

const BYTE _jung_code_to_2beol_lut[] = {
  'k' /* ㅏ 0 */,
  'o' /* ㅐ 1 */,
  'i' /* ㅑ 2 */,
  'O' /* ㅒ 3 */,
  'j' /* ㅓ 4 */,
  'p' /* ㅔ 5 */,
  'u' /* ㅕ 6 */,
  'P' /* ㅖ 7 */,
  'h' /* ㅗ 8 */,
  CHOJUNGJONG_NUL /* ㅘ 9 */,
  CHOJUNGJONG_NUL /* ㅙ 10 */,
  CHOJUNGJONG_NUL /* ㅚ 11 */,
  'y' /* ㅛ 12 */,
  'n' /* ㅜ 13 */,
  CHOJUNGJONG_NUL /* ㅝ 14 */,
  CHOJUNGJONG_NUL /* ㅞ 15 */,
  CHOJUNGJONG_NUL /* ㅟ 16 */,
  'b' /* ㅠ 17 */,
  'm' /* ㅡ 18 */,
  CHOJUNGJONG_NUL /* ㅢ 19 */,
  'l' /* ㅣ 20 */,
};

const ssize_t _jung_code_to_2beol_lut_len = 21;

const BYTE *_jung_chord_to_2beol_lut[] = {
  NULL /* ㅏ 0 */,  NULL /* ㅐ 1 */,  NULL /* ㅑ 2 */,  NULL /* ㅒ 3 */,
  NULL /* ㅓ 4 */,  NULL /* ㅔ 5 */,  NULL /* ㅕ 6 */,  NULL /* ㅖ 7 */,
  NULL /* ㅗ 8 */,  "hk" /* ㅘ 9 */,  "ho" /* ㅙ 10 */, "hl" /* ㅚ 11 */,
  NULL /* ㅛ 12 */, NULL /* ㅜ 13 */, "nj" /* ㅝ 14 */, "np" /* ㅞ 15 */,
  "nl" /* ㅟ 16 */, NULL /* ㅠ 17 */, NULL /* ㅡ 18 */, "ml" /* ㅢ 19 */,
};

const ssize_t _jung_chord_to_2beol_lut_len = 20;

const BYTE _jong_code_to_2beol_lut[] = {
  CHOJUNGJONG_NUL /* 0 */,
  'r' /* ㄱ 1 */,
  'R' /* ㄲ 2 */,
  CHOJUNGJONG_NUL /* ㄳ 3  */,
  's' /* ㄴ 4 */,
  CHOJUNGJONG_NUL /* ㄵ 5 */,
  CHOJUNGJONG_NUL /* ㄶ 6 */,
  'e' /* ㄷ 7 */,
  'f' /* ㄹ 8 */,
  CHOJUNGJONG_NUL /* ㄺ 9 */,
  CHOJUNGJONG_NUL /* ㄻ 10 */,
  CHOJUNGJONG_NUL /* ㄼ 11 */,
  CHOJUNGJONG_NUL /* ㄽ 12 */,
  CHOJUNGJONG_NUL /* ㄾ 13 */,
  CHOJUNGJONG_NUL /* ㄿ 14 */,
  CHOJUNGJONG_NUL /* ㅀ 15 */,
  'a' /* ㅁ 16 */,
  'q' /* ㅂ 17 */,
  CHOJUNGJONG_NUL /* ㅄ 18 */,
  't' /* ㅅ 19 */,
  'T' /* ㅆ 20 */,
  'd' /* ㅇ 21 */,
  'w' /* ㅈ 22 */,
  'c' /* ㅊ 23 */,
  'z' /* ㅋ 24 */,
  'x' /* ㅌ 25 */,
  'v' /* ㅍ 26 */,
  'g' /* ㅎ 27 */,
};

const ssize_t _jong_code_to_2beol_lut_len = 28;

const BYTE *_jong_chord_to_2beol_lut[] = {
  NULL /* 0 */,     NULL /* ㄱ 1 */,  NULL /* ㄲ 2 */,  "rt" /* ㄳ 3  */,
  NULL /* ㄴ 4 */,  "sw" /* ㄵ 5 */,  "sg" /* ㄶ 6 */,  NULL /* ㄷ 7 */,
  NULL /* ㄹ 8 */,  "fr" /* ㄺ 9 */,  "fa" /* ㄻ 10 */, "fq" /* ㄼ 11 */,
  "ft" /* ㄽ 12 */, "fx" /* ㄾ 13 */, "fv" /* ㄿ 14 */, "fg" /* ㅀ 15 */,
  NULL /* ㅁ 16 */, NULL /* ㅂ 17 */, "qt" /* ㅄ 18 */,
};

const ssize_t _jong_chord_to_2beol_lut_len = 19;

const hangeul_jamo_jaeum_unicode_2beol_row_t _jamo_jaeum_unicode_2beol_lut[]
    = {
        /* 0x3131 ㄱ */
        {
            .cjj = CHOSEONG,
            .code = 0,
            .unicode = 0x3131,
        },
        {
            .cjj = JONGSEONG,
            .code = 1,
            .unicode = 0x3131,
        },

        /* 0x3132 ㄲ */
        {
            .cjj = CHOSEONG,
            .code = 1,
            .unicode = 0x3132,
        },
        {
            .cjj = JONGSEONG,
            .code = 2,
            .unicode = 0x3132,
        },

        /* 0x3133 ㄳ */
        {
            .cjj = JONGSEONG,
            .code = 3,
            .unicode = 0x3133,
        },

        /* 0x3134 ㄴ */
        {
            .cjj = CHOSEONG,
            .code = 2,
            .unicode = 0x3134,
        },
        {
            .cjj = JONGSEONG,
            .code = 4,
            .unicode = 0x3134,
        },

        /* 0x3135 ㄵ */
        {
            .cjj = JONGSEONG,
            .code = 5,
            .unicode = 0x3135,
        },

        /* 0x3136 ㄶ */
        {
            .cjj = JONGSEONG,
            .code = 6,
            .unicode = 0x3136,
        },

        /* 0x3137 ㄷ */
        {
            .cjj = CHOSEONG,
            .code = 3,
            .unicode = 0x3137,
        },
        {
            .cjj = JONGSEONG,
            .code = 7,
            .unicode = 0x3137,
        },

        /* 0x3138 ㄸ */
        {
            .cjj = CHOSEONG,
            .code = 4,
            .unicode = 0x3138,
        },

        /* 0x3139 ㄹ */
        {
            .cjj = CHOSEONG,
            .code = 5,
            .unicode = 0x3139,
        },
        {
            .cjj = JONGSEONG,
            .code = 8,
            .unicode = 0x3139,
        },

        /* 0x313a ㄺ */
        {
            .cjj = JONGSEONG,
            .code = 9,
            .unicode = 0x313a,
        },

        /* 0x313b ㄻ */
        {
            .cjj = JONGSEONG,
            .code = 10,
            .unicode = 0x313b,
        },

        /* 0x313c ㄼ */
        {
            .cjj = JONGSEONG,
            .code = 11,
            .unicode = 0x313c,
        },

        /* 0x313d ㄽ */
        {
            .cjj = JONGSEONG,
            .code = 12,
            .unicode = 0x313d,
        },

        /* 0x313e ㄾ */
        {
            .cjj = JONGSEONG,
            .code = 13,
            .unicode = 0x313e,
        },

        /* 0x313f ㄿ */
        {
            .cjj = JONGSEONG,
            .code = 14,
            .unicode = 0x313f,
        },

        /* 0x3140 ㅀ */
        {
            .cjj = JONGSEONG,
            .code = 15,
            .unicode = 0x3140,
        },

        /* 0x3141 ㅁ */
        {
            .cjj = CHOSEONG,
            .code = 6,
            .unicode = 0x3141,
        },
        {
            .cjj = JONGSEONG,
            .code = 16,
            .unicode = 0x3141,
        },

        /* 0x3142 ㅂ */
        {
            .cjj = CHOSEONG,
            .code = 7,
            .unicode = 0x3142,
        },
        {
            .cjj = JONGSEONG,
            .code = 17,
            .unicode = 0x3142,
        },

        /* 0x3143 ㅃ */
        {
            .cjj = CHOSEONG,
            .code = 8,
            .unicode = 0x3143,
        },

        /* 0x3144 ㅄ */
        {
            .cjj = JONGSEONG,
            .code = 18,
            .unicode = 0x3144,
        },

        /* 0x3145 ㅅ */
        {
            .cjj = CHOSEONG,
            .code = 9,
            .unicode = 0x3145,
        },
        {
            .cjj = JONGSEONG,
            .code = 19,
            .unicode = 0x3145,
        },

        /* 0x3146 ㅆ */
        {
            .cjj = CHOSEONG,
            .code = 10,
            .unicode = 0x3146,
        },
        {
            .cjj = JONGSEONG,
            .code = 20,
            .unicode = 0x3146,
        },

        /* 0x3147 ㅇ */
        {
            .cjj = CHOSEONG,
            .code = 11,
            .unicode = 0x3147,
        },
        {
            .cjj = JONGSEONG,
            .code = 21,
            .unicode = 0x3147,
        },

        /* 0x3148 ㅈ */
        {
            .cjj = CHOSEONG,
            .code = 12,
            .unicode = 0x3148,
        },
        {
            .cjj = JONGSEONG,
            .code = 22,
            .unicode = 0x3148,
        },

        /* 0x3149 ㅉ */
        {
            .cjj = CHOSEONG,
            .code = 13,
            .unicode = 0x3149,
        },

        /* 0x314a ㅊ */
        {
            .cjj = CHOSEONG,
            .code = 14,
            .unicode = 0x314a,
        },
        {
            .cjj = JONGSEONG,
            .code = 23,
            .unicode = 0x314a,
        },

        /* 0x314b ㅋ */
        {
            .cjj = CHOSEONG,
            .code = 15,
            .unicode = 0x314b,
        },
        {
            .cjj = JONGSEONG,
            .code = 24,
            .unicode = 0x314b,
        },

        /* 0x314c ㅌ */
        {
            .cjj = CHOSEONG,
            .code = 16,
            .unicode = 0x314c,
        },
        {
            .cjj = JONGSEONG,
            .code = 25,
            .unicode = 0x314c,
        },

        /* 0x314d ㅍ */
        {
            .cjj = CHOSEONG,
            .code = 17,
            .unicode = 0x314d,
        },
        {
            .cjj = JONGSEONG,
            .code = 26,
            .unicode = 0x314d,
        },

        /* 0x314e ㅎ */
        {
            .cjj = CHOSEONG,
            .code = 18,
            .unicode = 0x314e,
        },
        {
            .cjj = JONGSEONG,
            .code = 27,
            .unicode = 0x314e,
        },
      };

const ssize_t _jamo_jaeum_unicode_2beol_lut_len
    = sizeof (_jamo_jaeum_unicode_2beol_lut)
      / sizeof (hangeul_jamo_jaeum_unicode_2beol_row_t);
