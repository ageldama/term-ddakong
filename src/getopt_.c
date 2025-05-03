/**
 * 커맨드라인 파라미터 처리
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "config.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "global_flags.h"

int verbose_flag = 1;
char *keylog_filename = NULL;
char *default_keylog_filename = "KEYLOG.txt";


void print_banner(FILE *fp)
{
  fprintf(fp, "# 따콩 입력기 (Ddakong) v%s\n", PACKAGE_VERSION);
  fprintf(fp, "# Copyright %s, 2025. All rights reserved.\n", PACKAGE_BUGREPORT);
  fprintf(fp, "# Licensed under GPLv3. (see `LICENSE')\n");
}


void
do_getopt (int argc, char **argv)
{
  int c;

  while ((c = getopt (argc, argv, "hqLl:")) != -1)
    switch (c)
      {
      case 'h':
        print_banner(stderr);
        fprintf (stderr, "Usage: %s [-h] [-q] [-l KEYLOG]\n", argv[0]);
        fprintf (stderr, "\tOption (-h) : Show help 도움말\n");
        fprintf (stderr, "\tOption (-q) : Quiet STDERR-에 메시지 쓰지 않기\n");
        fprintf (stderr, "\tOption (-l FILENAME) : Write keylog to specified "
                         "file - 지정한 파일에 키로깅\n");
        fprintf (stderr, "\tOption (-L) : Write keylog to `%s'\n",
                 default_keylog_filename);
        exit (EXIT_SUCCESS);
        break;

      case 'q':
        verbose_flag = 0;
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
          fprintf (stderr, "Unknown option character `0x%x'.\n", optopt);
        exit (EXIT_FAILURE);
        break;
      default:
        abort ();
      }

  if (verbose_flag)
    {
      fprintf (stderr, "getopt: verbose:%d keylog:%s\n", verbose_flag,
               keylog_filename);
    }
}
