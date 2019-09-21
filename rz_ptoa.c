#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static char hex_digit(unsigned long n)
{
  if (n < 10)
    return n + '0';
  else
    return n - 10 + 'a';
}

char *rz_ptoa(unsigned long n)
{
  char *res;
  int len;

  len = 12;
  if (!(res = malloc(sizeof(char) * len + 3)))
    return (NULL);
  ft_memset(res, '0', len);
  res[1] = 'x';
  res += len + 2;
  *res-- = '\0';
  while (--len > 0)
    {
      *res-- = hex_digit(n % 16);
      n = n / 16;
    }
  *res = hex_digit(n);
  res -= 2;
  return (res);
}
