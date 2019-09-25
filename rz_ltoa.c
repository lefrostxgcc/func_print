#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static int count(long n)
{
  int i;

  i = 1;
  if (n < 0)
    {
      n = -n;
      i++;
    }
  while (n > 9)
    {
      n = n / 10;
      i++;
    }
  return (i);
}

void rz_ltoa(char *res, long n)
{
  int len;
  int sign;

  if (n == (long) 9223372036854775808UL)
    {
      res[0] = '\0';
      ft_strcpy(res, "-9223372036854775808");
      return;
    }
  len = count(n);
  if ((sign = n < 0 ? 1 : 0))
    n = -n;
  res += len;
  *res-- = '\0';
  while (--len)
    {
      *res-- = n % 10 + '0';
      n = n / 10;
    }
  if (sign)
    *res = '-';
  else
    *res = n + '0';
}
