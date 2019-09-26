#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

void rz_ftoa(char *buf, struct arg_info *info, double arg)
{
  long intp;
  long fracp;
  long i;
  long v;

  intp = arg;
  arg -= intp;
  i = 0;
  if (arg < 0)
    arg = -arg;
  v = 1;
  while (i < info->precision)
    {
      v *= 10;
      i++;
    }
  arg *= v;
  arg += 1.0 / v;
  fracp = arg;
  rz_ltoa(buf, intp);
  int len1 = ft_strlen(buf);
  if (info->precision > 0)
    {
      buf[len1++] = '.';
      rz_ultoa(buf + len1, fracp, info->core);
      int len2 = ft_strlen(buf);
      int count = info->precision - (len2 - len1);
      if (count < 0)
	count = 0;
      ft_memset(buf + len2, '0', count);
      buf[len2 + count] = '\0';
    }
  else
    {
      buf[len1] = '\0';
    }
}
