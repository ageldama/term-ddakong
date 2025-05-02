#include "im_handler.h"
#include "hangeul.h"
#include "utf8_.h"
#include "im_handler_hangeul.h"
#include <ctype.h>

void
im_handler_status__empty (im_handler_status *p_status)
{
  p_status->im_mode = FALSE;
  p_status->toggle = IM_HANDLER_TOGGLE__OFF;
}


#define _UNICODE_OUTBUF_MAX 10
static UNICODE_32 _unicode_outbuf[_UNICODE_OUTBUF_MAX];

#define _UTF8_OUTBUF_MAX 10
static BYTE _utf8_outbuf[_UTF8_OUTBUF_MAX];

void
_write_unicode_as_utf8(const int fd, const ssize_t unicode_out_len)
{
  for (ssize_t i = 0 ; i < unicode_out_len ; i ++)
    {
      ssize_t utf8_len = unicode_to_utf8(_unicode_outbuf[i],
                                         _utf8_outbuf);
      if (utf8_len > 0)
        {
          write(fd, _utf8_outbuf, (size_t) utf8_len);
        }
    }
}


void
handle_stdin_write_as_read
(
 const int fd_child,
 BYTE *buf, const ssize_t n_read,
 handle_write_to_child_cb_t write_cb, void *write_cb_aux
)
{
  ssize_t n_written = write (fd_child, buf, (size_t)n_read);

  if (NULL != write_cb)
    {
      write_cb (n_written, buf, write_cb_aux);
    }
}


void handle_stdin_write_remain (const int fd_child)
{
  // remain status->commit & clear
  UNICODE_32 unich =
    hangeul_flush_automata_status (&_hangeul_avtomat);
  if (unich != 0x00)
    {
      _unicode_outbuf[0] = unich;
      _write_unicode_as_utf8(fd_child, 1);
    }
}


void
handle_stdin (im_handler_status *p_status, const int fd_keyin,
              const int fd_child, BYTE *buf, const ssize_t buf_max,
              handle_write_to_child_cb_t write_cb, void *write_cb_aux)
{
  ssize_t n_read = read (fd_keyin, buf, (size_t)buf_max);
  if (n_read < 0)
    ;
  else if (n_read > 0)
    {
      if (n_read == 1 && buf[0] == 0x08 /* C-h */)
        {
          /* TOGGLE key */
          p_status->im_mode = ~(p_status->im_mode);

          if (p_status->im_mode == FALSE)
            {
              handle_stdin_write_remain (fd_child);
            }

          if (p_status->toggle == IM_HANDLER_TOGGLE__OFF)
            {
              /* 1st TOGGLE */
              p_status->toggle = IM_HANDLER_TOGGLE__ONCE;
              return;
            }
          else
            {
              /* 2nd consequent TOGGLE */
              p_status->toggle = IM_HANDLER_TOGGLE__OFF;

              handle_stdin_write_as_read(fd_child, buf, n_read,
                                         write_cb, write_cb_aux);
            }
        }
      else
        {
          /* NON-TOGGLE key */
          p_status->toggle = IM_HANDLER_TOGGLE__OFF;

          if (p_status->im_mode)
            {
              if (n_read >= 1 && buf[0] == 0x1b)
                {
                  /* im=enabled & input=ansi-seq => flush + passthru */
                  handle_stdin_write_remain (fd_child);
                  handle_stdin_write_as_read(fd_child, buf, n_read,
                                             write_cb, write_cb_aux);
                }
              else
                {
                  /* im=enabled => ... */
                  for (int i = 0 ; i < n_read ; i ++)
                    {
                      ssize_t unicode_out_len =
                        hangeul_2beol_fill(buf[i], &_hangeul_avtomat,
                                           _unicode_outbuf, _UNICODE_OUTBUF_MAX);
                      _write_unicode_as_utf8(fd_child, unicode_out_len);
                    }
                }
            }
          else
            {
              /* im=disabled => passthru. */
              handle_stdin_write_as_read(fd_child, buf, n_read,
                                         write_cb, write_cb_aux);
            }
        }
    }
}
