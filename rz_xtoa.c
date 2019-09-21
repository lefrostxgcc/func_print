#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static int count(unsigned long n)
{
  int i;

  i = 1;
  while (n > 15)
    {
      n = n / 16;
      i++;
    }
  return (i);
}

static char hex_digit(unsigned long n)
{
  if (n < 10)
    return n + '0';
  else
    return n - 10 + 'a';
}

char *rz_xtoa(unsigned long n)
{
  char *res;
  int len;

  len = count(n);
  if (!(res = malloc(sizeof(char) * len + 1)))
    return (NULL);
  res += len;
  *res-- = '\0';
  while (--len)
    {
      *res-- = hex_digit(n % 16);
      n = n / 16;
    }
  *res = hex_digit(n);
  return (res);
}
