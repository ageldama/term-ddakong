#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global_flags.h"

int verbose_flag = 1;
char *keylog_filename = NULL;
char *default_keylog_filename = "KEYLOG.txt";

void
do_getopt(int argc, char **argv)
{
  int c;

  while ((c = getopt (argc, argv, "hvLl:")) != -1)
    switch (c)
      {
      case 'h':
        fprintf(stderr, "Usage: %s [-h] [-q] [-l KEYLOG]\n", argv[0]);
        fprintf(stderr, "\tOption (-h) : Show help 도움말\n");
        fprintf(stderr, "\tOption (-q) : Quiet STDERR-에 메시지 쓰지 않기\n");
        fprintf(stderr, "\tOption (-l FILENAME) : Write keylog to specified file - 지정한 파일에 키로깅\n");
        fprintf(stderr, "\tOption (-L) : Write keylog to `%s'\n", default_keylog_filename);
        exit(EXIT_SUCCESS);
        break;

      case 'q':
        verbose_flag = ~verbose_flag;
        break;

      case 'l':
        keylog_filename = optarg;
        break;

      case 'L':
        keylog_filename = default_keylog_filename;
        break;

      case '?':
        if (optopt == 'l')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `0x%x'.\n",
                   optopt);
        exit(EXIT_FAILURE);
        break;
      default:
        abort ();
      }

  if (verbose_flag)
    {
      fprintf(stderr, "getopt: verbose:%d keylog:%s\n", verbose_flag, keylog_filename);
    }
}
