/**
 * Utilities for "Unix file-descriptor"
 *
 * Copyright 2025 Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef fd_io_h
#define fd_io_h 1

#include <sys/types.h>

#include "extern_.h"

/**
 * read(src_fd) >> write(dst_fd).
 *
 * `src_fd'-의 모든 내용을 읽지 않고, 지금 available-한 내용만
 * `buf_max'-만큼만 읽어서 복사.
 *
 * @param src_fd read()-수행할 file-descriptor
 *
 * @param dst_fd write()-할 file-descriptor
 *
 * @param buf read()-에서 사용할 버퍼 (non-null: 미리 할당된 버퍼여야
 * 함)
 *
 * @param buf_max `buf'-의 최대크기
 *
 * @return read하여 write한 바이트갯수 (음수, 0일 수 있음)
 */
EXTERN_ ssize_t cp_fd (const int src_fd, const int dst_fd, char *buf,
                       const ssize_t buf_max);

/**
 * 지정한 `fd'-을 non-blocking mode으로 설정
 *
 * @param fd fcntl() 적용할 file-descriptor
 *
 * @param p_old_fl `fd'-의 원래 fcntl()-세팅값을 전달하는
 * out-param.(nullable: NULL으로 지정하면 전달하지 않음
 *
 * @return fcntl() 실행결과 리턴값 그대로.
 */
EXTERN_ int fcntl_nb (const int fd, int *p_old_fl);

/**
 * file-descriptor을 epoll-file-descriptor에 추가하기
 *
 * @param epollfd target epoll-fd
 *
 * @param fd 추가할 file-descriptor
 *
 * @return epoll_ctl()-함수의 리턴값 그대로.
 */
EXTERN_
int epoll__add (const int epollfd, const int fd);

#endif /* ! fd_io_h */
