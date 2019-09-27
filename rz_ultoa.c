#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static unsigned flag_base(enum flag_type flag)
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

static int digit_count(unsigned long n, unsigned base)
{
  int i;

  i = 1;
  while (n > base - 1)
    {
      n = n / base;
      i++;
    }
  return (i);
}

void rz_ultoa(char *res, unsigned long n, enum flag_type flag)
{
  int len;
  int base;

  base = flag_base(flag);
  len = digit_count(n, base);
  res += len;
  *res-- = '\0';
  while (--len)
    {
      *res-- = digit_char(n % base, flag);
      n = n / base;
    }
  *res = digit_char(n % base, flag);
}
