/**
 * ddakong DLL plugin example: input handler
 *
 * Copyright Jonghyouk Yun <ageldama@gmail.com>, 2025. All rights
 * reserved. Use of this source code is governed by a GPLv3 license
 * that can be found in the license file.
 */

#include "config.h"
#include "plugin-api.h"

#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const char *_random_phrases[] = {
  "foo",
  "bar",
  "zoo",
  "spam",
  "eggs",

  "그대가 부모로 부터 물려받은 것도 없고 하늘로 부터 물려받은 것도 없는 "
  "처지라면 "
  "그대의 인생 길은 당연히 비포장 도로처럼 울퉁불퉁 할 수 밖에 없다. "
  "그리고 수많은 장애물을 만날 수 밖에 없다. "
  "그러나 두려워 하지 말라!! "
  "하나의 장애물은 하나의 경험이고 하나의 경험은 하나의 지혜다. "
  "모든 성공은 언제나 장애물 뒤에서 그대가 오기를 기다리고있다. ",

  "세상이 변하기를 소망하지 말고 그대 자신이 변하기를 소망하라. "
  "세상에게 바라는 것이 많은 사람에게는 불만과 실패라는 이름의 불청객이 "
  "찾아와서 포기를 종용하고 "
  "자신에게 바라는 것이 많은 사람에게는 성공과 희망이라는 이름의 초청객이 "
  "찾아와서 도전을 장려한다. "
  "그대 인생의 주인은 세상이 아니라 그대 자신이다.",

  "가지고 싶은 건 한없이 많은데 주고 싶은 건 하나도 없는 사람을 가까이 하지 "
  "말라. "
  "끝없이 먹기는 하는데 절대로 배설은 하지 않는 습성때문에 "
  "뱃속에 똥만 가득 들어차 있는 사람이라면 이미 인간이기를 포기한 사람으로 "
  "간주해도 무방하다.",

  "많이 아는 사람이 되려고 노력하기보다는 많이 느끼는 사람이 되려고 노력하라. "
  "많이 느끼는 사람이 되려고 노력하기보다는 많이 깨닫는 사람이 되려고 "
  "노력하라.",

  "그대여 결코 서두르지 마라 "
  "대어를 낚으려는 조사일수록 기다림이 친숙하고 "
  "먼 길을 떠나는 나그네일수록 서둘러 신발끈을 매지 않는다. ",

  "길이 있어 내가 가는 것이 아니라 내가 가서 길이 생기는 것이다.",

  "버려야할것이 무엇인지 아는 순간부터,나무는 가장아름답게 불탄다.",

  "태산같이 높은 지식도 티끌 같은 깨달음 한번에 무너져 버린다.",

  "한번 밖에 오지 않는 최고의 기회가 모두에게 주어졌다.",
};

const ssize_t _random_phrases_len = sizeof (_random_phrases) / sizeof (char *);

int _initialized = 0;

void
handle_input (im_handler_status *p_status, const int fd_keyin,
              const int fd_child, BYTE *buf, const ssize_t buf_max,
              handle_write_to_child_cb_t write_cb, void *write_cb_aux)
{
  if (!_initialized)
    {
      _initialized++;
      srand (time (NULL));
    }

  ssize_t n_read = read (fd_keyin, buf, (size_t)buf_max);
  if (n_read < 0)
    ;
  else if (n_read == 1 && isalpha (buf[0]))
    {
      const char *phrase = _random_phrases[rand () % _random_phrases_len];
      ssize_t n_written = write (fd_child, phrase, strlen (phrase));
      if (write_cb != NULL)
        {
          write_cb (n_written, buf, write_cb_aux);
        }
    }
  else
    {
      /* => passthru. */
      ssize_t n_written = write (fd_child, buf, n_read);
      if (write_cb != NULL)
        {
          write_cb (n_written, buf, write_cb_aux);
        }
    }
}
