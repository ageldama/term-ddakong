/**
 * "poll-fd" portable file-descriptor polling abstration
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#ifndef pollfd_h /* I know this is terrible naming */
#define pollfd_h 1

#include "extern_.h"

#include "config.h"

#include <stdint.h>

#if (ENABLE_SELECT)
#include "pollfd__select.h"
#elif (HAVE_SYS_EPOLL_H)
#include "pollfd__linux_epoll.h"
#elif (HAVE_KQUEUE)
#include "pollfd__kqueue.h"
#else
/* fallback */
#include "pollfd__select.h"
#endif

typedef enum
{
  pollfd_evt_in = 1,
  pollfd_evt_out,
} pollfd_evt_type;

/**
 * pollfd 구현방식 이름 문자열
 *
 * @return "epoll" / "select" / "kqueue"
 */
const char *pollfd_impl_name (void);

/**
 * file-descriptor event poller 생성
 *
 * select/epoll/kqueue abstraction
 *
 * @param max_evts polling-할 최대 이벤트 갯수
 *
 * @param timeout_millis polling timeout (milliseconds)
 *
 * @return 에러시엔 NULL
 */
EXTERN_
pollfd_t *pollfd_new (const size_t max_evts, const int timeout_millis);

/**
 * pollfd_t 메모리해제
 *
 * 연관된 모든 fd들도 polling에서 자동해제
 *
 * @param p_pollfd (non-nullable)
 */
EXTERN_
void pollfd_free (pollfd_t *p_pollfd);

/**
 * polling-할 fd 추가
 *
 * @param p_pollfd (non-nullable)
 *
 * @param fd file-descriptor
 *
 * @param evt_type event-type: input/output
 */
EXTERN_
int pollfd_add (pollfd_t *p_pollfd, const int fd,
                const pollfd_evt_type evt_type);

/**
 * polling
 *
 * @param p_pollfd (non-nullable)
 *
 * @param fds 이벤트가 발생한 file-descriptor을 수신할 배열
 *
 * @param fds_len `fds'-배열의 크기
 *
 * @return 몇 개의 이벤트가 발생했는지
 */
EXTERN_
int pollfd_wait (pollfd_t *p_pollfd, int *fds, const size_t fds_len);

#endif /* ! pollfd_h */
