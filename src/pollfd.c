/**
 * "poll-fd" portable file-descriptor polling abstration
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "pollfd.h"


#if (ENABLE_SELECT)
#include "pollfd__select.c"
#elif (HAVE_SYS_EPOLL_H)
#include "pollfd__linux_epoll.c"
#else
/* fallback */
#include "pollfd__select.c"
#endif
