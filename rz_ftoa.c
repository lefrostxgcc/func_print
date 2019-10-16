#include "rz_printf.h"

static unsigned long rz_modfl(long double n, int precision, long *i)
{
    unsigned long f;

    *i = n;
    n -= *i;
    if (n < 0)
	n = -n;
    if (precision == 0 && n >= 0.5)
	*i += rz_tern_l(*i > 0, 1, -1);
    if (precision > 18)
	precision = 18;
    n *= rz_pow(10, precision);
    f = n;
    n *= 10;
    if (((unsigned long) n) % 10 >= 5)
	f++;
    return (f);
}

int rz_ftoa(char *buf, t_rz_arg *arg, long double n)
{
    char frep[21];
    long i;
    unsigned long f;
    int f_len;
    int buf_len;
    int zero_count;
    int zero_pre;

    if (n < 0)
	arg->negative = 1;
    f = rz_modfl(n, arg->precision, &i);
    buf_len = rz_ltoa(buf, arg, i);
    if (arg->precision > 0 || arg->sharp)
	buf[buf_len++] = '.';
    if (arg->precision > 0)
    {
	zero_pre = 0;
	frep[0] = '\0';
	f_len = rz_ultoa(frep, arg, f);
	if (arg->precision > f_len)
	{
	    zero_pre = arg->precision - f_len;
	    rz_memset(buf + buf_len, '0', zero_pre);
	    buf_len += zero_pre;
	}
	rz_memcpy(buf + buf_len, frep, f_len);
	buf_len += f_len;
	zero_count = arg->precision - f_len - zero_pre;
	if (zero_count > 0)
	    arg->floatzero = zero_count;
    }
    buf[buf_len] = '\0';
    return (buf_len);
}
