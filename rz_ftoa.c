#include "rz_printf.h"
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

static unsigned long rz_modfl(long double n, int precision, long *i)
{
    unsigned long f;

    *i = n;
    n -= *i;
    if (n < 0)
	n = -n;
    if (precision == 0 && n >= 0.5)
      *i += rz_ternary(*i > 0, 1, -1);
    n *= rz_pow(10, precision);
    f = n;
    n *= 10;
    if (((unsigned long) n) % 10 >= 5)
	f++;
    return (f);
}

int rz_ftoa(char *buf, t_rz_arg *arg, long double n)
{
    long i;
    unsigned long f;
    int f_len;
    int buf_len;
    int zero_count;

    f = rz_modfl(n, arg->precision, &i);
    buf_len = rz_ltoa(buf, i);
    if (arg->precision > 0 || arg->sharp)
      buf[buf_len++] = '.';
    if (arg->precision > 0)
    {
	f_len = rz_ultoa(buf + buf_len, f, arg->type);
	buf_len += f_len;
	zero_count = arg->precision - f_len;
	if (zero_count > 0)
	{
	    ft_memset(buf + buf_len, '0', zero_count);
	    buf_len += zero_count;
	}
    }
    buf[buf_len] = '\0';
    return (buf_len);
}
