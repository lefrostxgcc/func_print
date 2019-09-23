#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static unsigned flag_size(enum flag_type flag)
{
  if (flag == f_o)
    return 8;
  else if (flag == f_x || flag == f_X || flag == f_p)
    return 16;
  return 10;
}

static char digit_char(unsigned long n, enum flag_type type)
{
  if (n < 10)
    return n + '0';
  else
    return n - 10 + (type == f_X ? 'A' : 'a');
}

static int count(unsigned long n, unsigned size)
{
  int i;

  i = 1;
  while (n > size - 1)
    {
      n = n / size;
      i++;
    }
  return (i);
}

char *rz_ultoa(unsigned long n, enum flag_type flag)
{
  char *res;
  int len;
  unsigned size;

  size = flag_size(flag);
  len = flag == f_p ? 12 : count(n, size);
  if (!(res = malloc(sizeof(char) * len + (flag == f_p ? 3 : 1))))
    return (NULL);
  if (flag == f_p)
    {
      ft_memset(res, '0', len);
      res[1] = 'x';
      res += 2;
    }
  res += len;
  *res-- = '\0';
  while (--len)
    {
      *res-- = digit_char(n % size, flag);
      n = n / size;
    }
  *res = digit_char(n % size, flag);
  if (flag == f_p)
    res -= 2;
  return (res);
}
