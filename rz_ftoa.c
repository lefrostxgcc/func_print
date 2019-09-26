#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

void rz_ftoa(struct arg_info *info, double arg, long *intp, unsigned long *fracp)
{
  int precision;
  int i;

  *intp = (long) arg;
  arg -= *intp;
  precision = info->precision;
  if (precision < 0)
    precision = 6;
  i = 0;
  while (i < precision)
    {
      arg *= 10;
      i++;
    }
  info->precision = -1;
  *fracp = arg;
}
