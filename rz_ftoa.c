#include <stdlib.h>
#include "rz_numtostr.h"
#include "libft/libft.h"

static void extract_int_frac(long double arg, int precision, long *intp, unsigned long *fracp)
{
  long i;
  long v;

  *intp = arg;
  arg -= *intp;
  if (arg < 0)
    arg = -arg;
  if (precision == 0 && arg >= 0.5)
    (*intp)++;
  i = 0;
  v = 1;
  while (i < precision)
    {
      v *= 10;
      i++;
    }
  arg *= v;
  arg += 1.0 / v;
  *fracp = arg;
}

static void fill_frac(char *buf, struct arg_info *info, unsigned long fracp)
{
  int int_len;
  int total_len;
  int zero_count;

  total_len = int_len = ft_strlen(buf);
  if (info->precision > 0)
    {
      buf[total_len++] = '.';
      rz_ultoa(buf + total_len, fracp, info->core);
      total_len = ft_strlen(buf);
      zero_count = info->precision - (total_len - 1 - int_len);
      if (zero_count > 0)
	{
	  ft_memset(buf + total_len, '0', zero_count);
	  total_len += zero_count;
	}
      buf[total_len] = '\0';
    }
}

void rz_ftoa(char *buf, struct arg_info *info, long double arg)
{
  long intp;
  unsigned long fracp;

  extract_int_frac(arg, info->precision, &intp, &fracp);
  rz_ltoa(buf, intp);
  fill_frac(buf, info, fracp);
}
