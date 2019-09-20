#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static int count(unsigned long n)
{
  int i;

  i = 1;
  while (n > 9)
    {
      n = n / 10;
      i++;
    }
  return (i);
}

char *rz_ultoa(unsigned long n)
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
      *res-- = n % 10 + '0';
      n = n / 10;
    }
  *res = n + '0';
  return (res);
}
