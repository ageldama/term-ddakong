/**
 * 한글/2벌식 => 유니코드 오토마타
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
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

/**
 * 한글자모 유니코드으로 조합
 *
 * @see hangeul_jamo_jaeum_to_unicode()
 *
 * @param cho 초성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jung 중성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jong 종성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @return 변환된 자모한글 유니코드 포인트. 변환실패시 0x00.
 */
EXTERN_ UNICODE_32 hangeul_jamo_compose_to_unicode (const BYTE cho,
                                                    const BYTE jung,
                                                    const BYTE jong);

/**
 * 한글자모 1-개소만 유니코드표 이용하여 변환
 *
 * @see _jamo_jaeum_unicode_2beol_lut_len
 *
 * @param cjj 초중종 구분
 *
 * @param 변환할 초중종 LUT-inedx
 *
 * @return 변환된 유니코드 포인트. 변환실패시 0x00.
 */
EXTERN_ UNICODE_32 hangeul_jamo_jaeum_to_unicode (const CHOJUNGJONG cjj,
                                                  const BYTE code);

/**
 * 초중종 조합이 부분자모를 나타내는 상태인지?
 *
 * @param cho 초성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jung 중성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @param jong 종성 LUT-index (CHOJUNGJONG_NUL 가능)
 *
 * @return BOOL
 */
EXTERN_ BOOL hangeul_partial_jamo_p (const BYTE cho, const BYTE jung,
                                     const BYTE jong);

/**
 * 한글2벌식오토마타 상태구조체가 완전 비어 있는 상태인지?
 *
 * @param p_status (nullable) NULL이면 그것도 TRUE
 */
EXTERN_ BOOL
hangeul_empty_automata_status_p (const hangeul_automata_status *p_status);

/**
 * 한글2벌식 알파벳 입력을 자음/모음으로 구분
 *
 * @param ch 입력 char 문자 (예: 'c', 'a')
 *
 * @return 자모음구분
 */
EXTERN_ JAMOEUM hangeul_2beol_alpha_as_jamoeum (const BYTE ch);

/**
 * 한글2벌식오토마타 구현 함수
 *
 * 입력 문자 ch을 한글으로 조합하여 outbuf에 출력.
 *
 * 가능하면, 한글2벌식 키보드에 대응되는 문자(알파벳)만을 전달할 것.
 *
 * 다른 입력코드들을 받으면 변환 않고 그대로 passthrough하지만, ANSI
 * Code Sequence등과 같이 2번째 바이트부터 구분이 어려운 경우엔
 * 한글코드으로 이해하여 문제가 생길 수 있으므로.
 *
 * @param ch 입력 문자 (char)
 *
 * @param p_status 한글오토마타 상태구조체
 *
 * @param outbuf 출력버퍼
 *
 * @param outbuf_max 출력버퍼의 전체크기
 *
 * @return 출력버퍼에 출력한 유니코드 코드포인트 갯수
 */
EXTERN_ ssize_t hangeul_2beol_fill (const BYTE ch,
                                    hangeul_automata_status *p_status,
                                    UNICODE_32 *outbuf,
                                    const ssize_t outbuf_max);

/**
 * 한글2벌식 초중종에 따른 입력 알파벳코드 => LUT-index 변환
 *
 * @param chojungjong 변환할 알파벳에 대입할 초중종-구분
 *
 * @param ch 변환할 입력 알파벳 char. (예: 'a')
 *
 * @return 변환한 결과 LUT-index, 변환 실패시 CHOJUNGJONG_NUL.
 */
EXTERN_ BYTE hangeul_2beol_find_code (const CHOJUNGJONG chojungjong,
                                      const BYTE ch);

/**
 * 한글2벌식 이중자음으로 합치기
 *
 * 예: ㄱ(r) + ㄱ(r) => ㄲ(rr)
 *
 * @param chojungjong 초중종 구분
 *
 * @param prev_ch 이전 입력 알파벳 char
 *
 * @param ch 이번 입력 알파벳 char
 *
 * @return 변환한 결과 LUT-index, 변환 실패시 CHOJUNGJONG_NUL.
 */
EXTERN_ BYTE hangeul_double_jaeum (const CHOJUNGJONG chojungjong,
                                   const BYTE prev_ch, const BYTE ch);

/**
 * 유니코드 포인트 정수값을 outbuf에 출력
 *
 * *p_pos-의 현재 위치가 outbuf_max에 같거나 넘어서면,
 *  assertion-error.
 *
 * @param outbuf 출력버퍼
 *
 * @param outbuf_max 출력버퍼크기
 *
 * @param p_pos (non-null) [in] 출력전 버퍼위치, [out] 출력후 새
 * 버퍼위치.
 *
 * @param ch 출력할 유니코드 포인트 정수값
 */
EXTERN_ void hangeul_put_unicode (UNICODE_32 *outbuf, const ssize_t outbuf_max,
                                  ssize_t *p_pos, UNICODE_32 ch);

/**
 * 한글2벌식오토마타: 종성 코드를 쌍자음인 경우, 좌/우 자음으로 분리
 *
 * 실은 단자음의 경우에도 처리해줌.
 *
 * @param jongseong 처리할 종성 LUT-index 코드값
 *
 * @param pout_left 좌측 출력 (예: "값"/"ㅂㅅ" => "ㅂ") 단자음,
 * 쌍자음의 경우 왼편자음을 대응. 종성이 없었다면 세팅 않음.
 *
 * @param pout_right 우측 출력 (예: "값"/"ㅂㅅ" => "ㅅ") 쌍자음일
 * 경우에만 세팅. 쌍자음의 오른쪽 부분.
 *
 * @return 분해한 출력의 갯수. 처리불가했다면=0, 단자음이었다면=1,
 * 쌍자음이었다면=2.
 */
EXTERN_ int hangeul_decompose_jongseong (const BYTE jongseong, BYTE *pout_left,
                                         BYTE *pout_right);

/**
 * 한글2벌식오토마타 상태구조체의 조합가능한 유니코드가 있다면,
 * 출력하고, 상태구조체도 비움.
 *
 * @see hangeul_flush_automata_status()
 *
 * @see hangeul_put_unicode()
 *
 * @param p_status (non-null)
 *
 * @param outbuf (non-null) 출력버퍼
 *
 * @param outbuf_max 출력버퍼의 크기
 *
 * @param p_cur_pos (non-null) [in] 현재 버퍼위치 / [out] 출력후 버퍼위치
 *
 * @return 조합해낸 유니코드 코드포인트, 조합+출력하지 않았다면 0x00.
 */
EXTERN_ UNICODE_32 hangeul_2beol_commit_1_and_flush (
    hangeul_automata_status *p_status, UNICODE_32 *outbuf,
    const ssize_t outbuf_max, ssize_t *p_cur_pos);

/**
 * 한글2벌식오토마타 입력 알파벳 코드를 즉시 한글자모 유니코드으로
 * 변환하여 버퍼에 출력.
 *
 * 한글자모 유니코드으로 변환이 성공했을 때에만 출력.
 *
 * @see hangeul_2beol_find_code()
 *
 * @see hangeul_jamo_compose_to_unicode()
 *
 * @see hangeul_put_unicode()
 *
 * @param outbuf (non-null) 출력버퍼
 *
 * @param outbuf_max 출력버퍼의 크기
 *
 * @param p_pos (non-null) [in] 출력버퍼의 현재위치 / [out] 출력버퍼의
 * 새 위치
 *
 * @param cjj 초중종 구분
 *
 * @param ch 입력 알파벳 문자
 *
 * @return 자모 유니코드 코드포인트값, 변환실패했다면 0x00.
 */
EXTERN_ UNICODE_32 hangeul_put_jamo_unicode (UNICODE_32 *outbuf,
                                             const ssize_t outbuf_max,
                                             ssize_t *p_pos, CHOJUNGJONG cjj,
                                             BYTE ch);

/**
 * 한글2벌식 초중종에 따른 LUT-index 코드값을 다른 초중종에 매칭되는
 * 코드값으로 변환
 *
 * 원래의 입력 알파벳값을 찾아, 다른 초중종-테이블에서 대응되는
 * 코드값으로 다시 찾기
 *
 * 2중 자음은 대문자변환된 형태로만 지원함.
 *
 * (예: 'ㄲ' => R (OK) rr (NO)).
 *
 * @see hangeul_2beol_find_code()
 *
 * @param from_cjj 입력 from_code 의 초중종 구분
 *
 * @param to_cjj 변환될 목표 초중종 구분
 *
 * @param from_code 입력 LUT-index 코드
 *
 * @return 변환된 to_cjj 에 대응되는 LUT-index 코드. 찾지 못하면
 * CHOJUNGJONG_NUL.
 */
EXTERN_ BYTE hangeul_remap_code (const CHOJUNGJONG from_cjj,
                                 const CHOJUNGJONG to_cjj,
                                 const BYTE from_code);

/**
 * 한글2벌식 알파벳 입력 대응 초성 코드표
 *
 * @see hangeul_2beol_find_code()
 */
EXTERN_ const BYTE _cho_code_to_2beol_lut[];

/**
 * 한글2벌식 알파벳 입력 대응 초성 코드표의 길이
 *
 * @see hangeul_2beol_find_code()
 */
EXTERN_ const ssize_t _cho_code_to_2beol_lut_len;

/**
 * 한글2벌식 초성/쌍자음 입력 코드표
 *
 * @see hangeul_double_jaeum()
 */
EXTERN_ const BYTE *_cho_chord_to_2beol_lut[];

/**
 * 한글2벌식 초성/쌍자음 입력 코드표의 길이
 *
 * @see hangeul_double_jaeum()
 */
EXTERN_ const ssize_t _cho_chord_to_2beol_lut_len;

/**
 * 한글2벌식 알파벳 입력 대응 중성 코드표
 *
 * @see hangeul_2beol_find_code()
 */
EXTERN_ const BYTE _jung_code_to_2beol_lut[];

/**
 * 한글2벌식 알파벳 입력 대응 중성 코드표의 길이
 *
 * @see hangeul_2beol_find_code()
 */
EXTERN_ const ssize_t _jung_code_to_2beol_lut_len;

/**
 * 한글2벌식 중성/합성모음 입력 코드표
 *
 * 예: ㅗ(h) +ㅣ(l) => ㅚ
 *
 * @see hangeul_double_jaeum() 함수이름은 "자음"이지만 모음도 처리, 데헷.
 */
EXTERN_ const BYTE *_jung_chord_to_2beol_lut[];

/**
 * 한글2벌식 중성/합성모음 입력 코드표의 길이
 *
 * @see hangeul_double_jaeum() 함수이름은 "자음"이지만 모음도 처리, 데헷.
 */
EXTERN_ const ssize_t _jung_chord_to_2beol_lut_len;

/**
 * 한글2벌식 알파벳 입력 대응 종성 코드표
 *
 * @see hangeul_2beol_find_code()
 */
EXTERN_ const BYTE _jong_code_to_2beol_lut[];

/**
 * 한글2벌식 알파벳 입력 대응 종성 코드표의 길이
 *
 * @see hangeul_2beol_find_code()
 */
EXTERN_ const ssize_t _jong_code_to_2beol_lut_len;

/**
 * 한글2벌식 종성/쌍자음 입력 코드표
 *
 * @see hangeul_double_jaeum()
 */
EXTERN_ const BYTE *_jong_chord_to_2beol_lut[];

/**
 * 한글2벌식 종성/쌍자음 입력 코드표의 길이
 *
 * @see hangeul_double_jaeum()
 */
EXTERN_ const ssize_t _jong_chord_to_2beol_lut_len;

/**
 * 한글 자모/자음의 [입력코드 => 유티코드] 대응표
 *
 * @see hangeul_jamo_jaeum_to_unicode()
 */
EXTERN_ const hangeul_jamo_jaeum_unicode_2beol_row_t
    _jamo_jaeum_unicode_2beol_lut[];

/**
 * 한글 자모/자음의 [입력코드 => 유티코드] 대응표 길이
 *
 * @see hangeul_jamo_jaeum_to_unicode()
 */
EXTERN_ const ssize_t _jamo_jaeum_unicode_2beol_lut_len;

#endif /* ! hangeul__h */
