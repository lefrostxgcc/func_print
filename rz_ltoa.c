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

char *rz_ltoa(long n)
{
  char *res;
  int len;
  int sign;

  if (n == (long) 9223372036854775808UL)
    return (ft_strdup("-9223372036854775808"));
  len = count(n);
  if ((sign = n < 0 ? 1 : 0))
    n = -n;
  if (!(res = malloc(sizeof(char) * len + 1)))
    return (NULL);
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
  return (res);
}
