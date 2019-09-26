#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

void rz_ftoa(struct arg_info *info, double arg, long *intp, unsigned long *fracp)
{
  int precision;
  int i;
  int v;

  *intp = (long) arg;
  arg -= *intp;
  precision = info->precision;
  if (precision < 0)
    precision = 6;
  i = 0;
  if (arg < 0)
    arg = -arg;
  v = 1;
  while (i < precision)
    {
      v *= 10;
      i++;
    }
  arg *= v;
  arg += 1.0 / v;
  info->precision = -1;
  *fracp = arg;
}
