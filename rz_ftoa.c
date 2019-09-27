#include <stdlib.h>
#include "rz_printf_impl.h"
#include "libft/libft.h"

static unsigned long rz_pow(int base, int exp)
{
  unsigned long result;
  int i;

  result = 1;
  i = 0;
  while (i++ < exp)
    result *= base;
  return (result);
}

static void extract_int_frac(long double arg, int precision, long *intp, unsigned long *fracp)
{
  unsigned long frac_pow;
  double frac;

  *intp = arg;
  arg -= *intp;
  if (arg < 0)
    arg = -arg;
  if (precision == 0 && arg >= 0.5)
    *intp += *intp > 0 ? 1 : -1;
  frac_pow = rz_pow(10, precision);
  frac = arg * frac_pow;
  *fracp = frac;
  frac *= 10;
  if (((unsigned long) frac) % 10 >= 5)
    (*fracp)++;
 }

static void fill_frac(char *buf, struct rz_arg *info, unsigned long fracp)
{
  int int_len;
  int total_len;
  int zero_count;

  total_len = int_len = ft_strlen(buf);
  if (info->precision > 0)
    {
      buf[total_len++] = '.';
      rz_ultoa(buf + total_len, fracp, info->type);
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

void rz_ftoa(char *buf, struct rz_arg *info, long double arg)
{
  long intp;
  unsigned long fracp;

  extract_int_frac(arg, info->precision, &intp, &fracp);
  rz_ltoa(buf, intp);
  fill_frac(buf, info, fracp);
}
