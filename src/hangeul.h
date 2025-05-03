/**
 * 한글/2벌식 => 유니코드 오토마타
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef hangeul__h
#define hangeul__h 1

#include <unistd.h>

#include "err.h"
#include "extern_.h"
#include "typedef_.h"

#ifndef CHOJUNGJONG

/** 초중종-성 구분 타입 */
#define CHOJUNGJONG BYTE

/** 초중종-성 구분: 초성 */
#define CHOSEONG ((BYTE)0x01)
/** 초중종-성 구분: 중성 */
#define JUNGSEONG ((BYTE)0x02)
/** 초중종-성 구분: 종성 */
#define JONGSEONG ((BYTE)0x03)

/** 자음/모음 구분 타입 */
#define JAMOEUM BYTE
/** 자음 */
#define JAEUM ((BYTE)0x10)
/** 모음 */
#define MOEUM ((BYTE)0x20)

/**
 * 초중종/구분 비어 있음(NUL)-값
 */
#define CHOJUNGJONG_NUL ((BYTE)0xff)

#endif


/**
 * 한글 2벌식 오토마타 상태 구조체
 *
 * 상태값 초중성은 _cho_code_to_2beol_lut, _jung_code_to_2beol_lut,
 * _jong_code_to_2beol_lut 에서 찾아낸, 입력키(isalpha())-에 대응하는
 * 각 LUT의 인덱스 값.
 *
 * @see isalpha()
 *
 * @field stage 현재 오토마타 상태 (NA/초/중/종-입력됨)
 *
 * @field prev_ch 직전 입력된 키문자(char), 2중 자음 구현을 위해서.
 * (예: rr => ㄱ+ㄱ => ㄲ)
 *
 * @field cho 상태:초성 (CHOJUNGJONG_NUL 가능)
 *
 * @field jung 상태:중성 (CHOJUNGJONG_NUL 가능)
 *
 * @field jong 상태:종성 (CHOJUNGJONG_NUL 가능)
 */
typedef struct
{
  CHOJUNGJONG stage;
  BYTE prev_ch;

  BYTE cho;
  BYTE jung;
  BYTE jong;
} hangeul_automata_status;


/**
 * 한글 자모/자음의 [입력코드 => 유티코드] 대응표의 행 구조체
 *
 * 한글 자모 입력은 초중종-코드에 따라 상태보관하는데, 이를 조합된
 * 한글 1-글자가 아닌, 부분자모으로 유니코드 출력을 위해서 변환
 * 테이블이 필요.
 *
 * @field cjj 초중종-구분코드
 *
 * @field code 초중종에 따른 LUT-index값
 *
 * @field unicode 대응되는 한글자모 유니코드 포인트 정수값
 */
typedef struct
{
  CHOJUNGJONG cjj;
  BYTE code;
  UNICODE_32 unicode;
} hangeul_jamo_jaeum_unicode_2beol_row_t;

/**
 * 한글2벌식오토마타 상태구조체를 초기화
 *
 * 초중종-LUT-index을 빈 값으로, stage도 빈 값으로.
 * prev_ch도 NUL('\x00')으로.
 *
 * @param p_status (non-null)
 */
EXTERN_ void hangeul_clear_automata_status (hangeul_automata_status *p_status);

/**
 * 한글2벌식오토마타 잔여상태를 유니코드으로 변환하고, 상태구조체를
 * 초기화
 *
 * @see hangeul_clear_automata_status() 호출하여 상태구조체를 비움.
 *
 * @param p_status (non-null)
 *
 * @return 오토마타 상태구조체가 변환가능한 상태였을 경우에 변환한
 * 유니코드 코드, 그런 상태가 아니었다면 0x00 (NUL).
 */
EXTERN_ UNICODE_32
hangeul_flush_automata_status (hangeul_automata_status *p_status);

/**
 * 한글2벌식오토마타 상태로부터 자동으로 한글(full) -or- 한글자모에
 * 대응하는 유니코드값으로 변환.
 *
 * 한글자모으로라도 변환가능한 상태가 아니었다면, NUL코드값(0x00)
 *
 * @see hangeul_partial_jamo_p() 부분자모상태인지 확인을 위해 사용.
 *
 * @see hangeul_full_compose_to_unicode() 한글 1글자으로 변환시 사용.
 *
 * @see hangeul_jamo_compose_to_unicode() 한글자모 변환시 사용.
 *
 * @param cho 초성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jung 중성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jong 종성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @return 변환한 유니코드 코드, 변환가능한 상태가 아니었다면 0x00
 * (NUL).
 */
EXTERN_ UNICODE_32 hangeul_auto_compose_to_unicode (const BYTE cho,
                                                    const BYTE jung,
                                                    const BYTE jong);

/**
 * 한글2벌식오토마타 상태를 완전한 한글 1글자 유니코드으로 변환.
 *
 * @param cho 초성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jung 중성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jong 종성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @return 변환한 유니코드 코드, 항상 코드를 반환하는데 깨진
 * 한글유니코드일 수 있음. (입력에 주의)
 */
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
