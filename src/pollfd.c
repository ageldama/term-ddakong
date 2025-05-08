#include "pollfd.h"


#if (ENABLE_SELECT)
#include "pollfd__select.c"
#elif (HAVE_SYS_EPOLL_H)
#include "pollfd__linux_epoll.c"
#else
/* fallback */
#include "pollfd__select.c"
#endif
