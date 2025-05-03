/**
 * im_handler 표준입력 처리
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef im_handler_h
#define im_handler_h 1

#include <stdlib.h>
#include <unistd.h>

#include "extern_.h"
#include "typedef_.h"

#ifndef IM_HANDLER_TOGGLE_STATE

/** "toggle-key" 눌린 횟수 카운터 타입 */
#define IM_HANDLER_TOGGLE_STATE BYTE

/** "toggle-key" 눌리지 않음 */
#define IM_HANDLER_TOGGLE__OFF ((IM_HANDLER_TOGGLE_STATE)0)

/** "toggle-key" 한 번 눌림 */
#define IM_HANDLER_TOGGLE__ONCE ((IM_HANDLER_TOGGLE_STATE)1)

#endif /* ! IM_HANDLER_TOGGLE_STATE */

/**
 * 입력처리 이후 호출될 콜백함수의 타입
 *
 * @param n_written 출력한 바이트 갯수 (pty-child에)
 *
 * @param buf 출력내용을 담은 버퍼
 *
 * @param cb_aux 콜백에 전달할 추가 데이터 (closure)
 */
typedef void handle_write_to_child_cb_t (const ssize_t n_written,
                                         const BYTE *buf, void *cb_aux);

/**
 * 표준입력 처리기 상태
 *
 * @field im_mode "input-method"-mode 활성상태인지?
 *
 * @field toggle "toggle-key" 눌린 횟수 카운터
 */
typedef struct
{
  BOOL im_mode;
  IM_HANDLER_TOGGLE_STATE toggle;
} im_handler_status;


/**
 * 표준입력 처리기 상태 초기화
 *
 * @param p_status (non-null) 초기화할 상태값 구조체
 */
EXTERN_
void im_handler_status__empty (im_handler_status *p_status);

/**
 * 표준입력 처리 함수
 *
 * @see read
 *
 * @see write
 *
 * @param p_status (non-null) 상태구조체
 *
 * @param fd_keyin 입력을 read()-할 file-descriptor
 *
 * @param fd_child 입력을 write()-전달할 대상 file-descriptor
 *
 * @param buf 입력을 read()/read() 저장/전달할 버퍼
 *
 * @param buf_max `buf'-의 최대크기
 *
 * @param write_cb write()-이후에 호출할 콜백함수
 *
 * @param write_cb_aux 콜백함수 호출시 함께 전달할 데이터 (closure)
 */
EXTERN_
void handle_stdin (im_handler_status *p_status, const int fd_keyin,
                   const int fd_child, BYTE *buf, const ssize_t buf_max,
                   handle_write_to_child_cb_t write_cb, void *write_cb_aux);

#endif /* ! im_handler_h */
