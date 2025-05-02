#ifndef hangeul__h
#define hangeul__h 1

#include <unistd.h>

#include "err.h"
#include "extern_.h"
#include "typedef_.h"

#ifndef CHOJUNGJONG

#define CHOJUNGJONG BYTE
#define CHOSEONG ((BYTE)0x01)
#define JUNGSEONG ((BYTE)0x02)
#define JONGSEONG ((BYTE)0x03)

#define JAMOEUM BYTE
#define JAEUM ((BYTE)0x10)
#define MOEUM ((BYTE)0x20)

#define CHOJUNGJONG_NUL ((BYTE)0xff)

#endif

typedef struct
{
  CHOJUNGJONG stage;
  BYTE prev_ch;

  BYTE cho;
  BYTE jung;
  BYTE jong;
} hangeul_automata_status;

typedef struct
{
  CHOJUNGJONG cjj;
  BYTE code;
  UNICODE_32 unicode;
} hangeul_jamo_jaeum_unicode_2beol_row_t;

EXTERN_ void hangeul_clear_automata_status (hangeul_automata_status *p_status);

EXTERN_ UNICODE_32
hangeul_flush_automata_status (hangeul_automata_status *p_status);

EXTERN_ UNICODE_32 hangeul_auto_compose_to_unicode (const BYTE cho,
                                                    const BYTE jung,
                                                    const BYTE jong);

EXTERN_ UNICODE_32 hangeul_full_compose_to_unicode (const BYTE cho,
                                                    const BYTE jung,
                                                    const BYTE jong);

EXTERN_ UNICODE_32 hangeul_jamo_compose_to_unicode (const BYTE cho,
                                                    const BYTE jung,
                                                    const BYTE jong);

EXTERN_ UNICODE_32 hangeul_jamo_jaeum_to_unicode (const CHOJUNGJONG cjj,
                                                  const BYTE code);

EXTERN_ BOOL hangeul_partial_jamo_p (const BYTE cho, const BYTE jung,
                                     const BYTE jong);

EXTERN_ BOOL
hangeul_empty_automata_status_p (const hangeul_automata_status *p_status);

EXTERN_ JAMOEUM hangeul_2beol_alpha_as_jamoeum (const BYTE ch);

EXTERN_ ssize_t hangeul_2beol_fill (const BYTE ch,
                                    hangeul_automata_status *p_status,
                                    UNICODE_32 *outbuf,
                                    const ssize_t outbuf_max);

EXTERN_ BYTE hangeul_2beol_find_code (const CHOJUNGJONG chojungjong,
                                      const BYTE ch);

EXTERN_ BYTE hangeul_double_jaeum (const CHOJUNGJONG, const BYTE prev_ch,
                                   const BYTE ch);

EXTERN_ void hangeul_put_unicode (UNICODE_32 *outbuf, const ssize_t outbuf_max,
                                  ssize_t *p_pos, UNICODE_32 ch);

EXTERN_ int hangeul_decompose_jongseong (const BYTE jongseong, BYTE *pout_left,
                                         BYTE *pout_right);

EXTERN_ UNICODE_32 hangeul_2beol_commit_1_and_flush (
    hangeul_automata_status *p_status, UNICODE_32 *outbuf,
    const ssize_t outbuf_max, ssize_t *p_cur_pos);

EXTERN_ UNICODE_32 hangeul_put_jamo_unicode (UNICODE_32 *outbuf,
                                             const ssize_t outbuf_max,
                                             ssize_t *p_pos, CHOJUNGJONG cjj,
                                             BYTE ch);

EXTERN_ void hangeul_2beol_commit_2 (hangeul_automata_status *p_status,
                                     UNICODE_32 *outbuf,
                                     const ssize_t outbuf_max,
                                     ssize_t *p_cur_pos,
                                     CHOJUNGJONG chojungjong, BYTE ch);

EXTERN_ BYTE hangeul_remap_code (const CHOJUNGJONG from_cjj,
                                 const CHOJUNGJONG to_cjj,
                                 const BYTE from_code);

EXTERN_ const BYTE _cho_code_to_2beol_lut[];
EXTERN_ const ssize_t _cho_code_to_2beol_lut_len;

EXTERN_ const BYTE *_cho_chord_to_2beol_lut[];
EXTERN_ const ssize_t _cho_chord_to_2beol_lut_len;

EXTERN_ const BYTE _jung_code_to_2beol_lut[];
EXTERN_ const ssize_t _jung_code_to_2beol_lut_len;

EXTERN_ const BYTE *_jung_chord_to_2beol_lut[];
EXTERN_ const ssize_t _jung_chord_to_2beol_lut_len;

EXTERN_ const BYTE _jong_code_to_2beol_lut[];
EXTERN_ const ssize_t _jong_code_to_2beol_lut_len;

EXTERN_ const BYTE *_jong_chord_to_2beol_lut[];
EXTERN_ const ssize_t _jong_chord_to_2beol_lut_len;

EXTERN_ const hangeul_jamo_jaeum_unicode_2beol_row_t
    _jamo_jaeum_unicode_2beol_lut[];

EXTERN_ const ssize_t _jamo_jaeum_unicode_2beol_lut_len;

#endif /* ! hangeul__h */
