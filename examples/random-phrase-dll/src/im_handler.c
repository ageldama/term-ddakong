#include "config.h"
#include "plugin-api.h"

#include <unistd.h>
#include <ctype.h>


void
handle_input (im_handler_status *p_status, const int fd_keyin,
              const int fd_child, BYTE *buf, const ssize_t buf_max,
              handle_write_to_child_cb_t write_cb, void *write_cb_aux)
{
  ssize_t n_read = read (fd_keyin, buf, (size_t)buf_max);
  if (n_read < 0)
    ;
  else if (n_read == 1 && isalpha(buf[0]))
    {
    }
  else
    {
      /* => passthru. */
      ssize_t n_written = write(fd_child, buf, n_read);
      if (write_cb != NULL)
        {
          write_cb(n_written, buf, write_cb_aux);
        }
    }
}
