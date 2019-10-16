#include "rz_printf.h"

static unsigned long rz_modfl(long double n, int precision, long *i)
{
    unsigned long frac;
    unsigned long pre_pow;
    long double tn;

    *i = n;
    n -= *i;
    if (n < 0)
	n = -n;
    if (precision > 18)
	precision = 18;
    pre_pow = rz_pow(10, precision);
    n *= pre_pow;
    frac = n;
    tn = n - (unsigned long) n;
    tn *= 10;
    if (((unsigned long) tn) % 10 >= 5)
	frac++;
    if (frac >= pre_pow)
    {
	*i += rz_tern_l(*i > 0, 1, -1);
	frac = 0;
    }
    return (frac);
}

static int rz_ftoa_frac(char *buf, t_rz_arg *f, unsigned long frac)
{
    char frep[21];
    int zero_prefix;
    int zero_suffix;
    int total_len;
    int frac_len;
    
    zero_prefix = 0;
    frep[0] = '\0';
    frac_len = rz_ultoa(frep, f, frac);
    total_len = frac_len;
    if (f->precision > frac_len)
    {
	zero_prefix = f->precision - frac_len;
	rz_memset(buf, '0', zero_prefix);
	total_len += zero_prefix;
    }
    rz_memcpy(buf + zero_prefix, frep, frac_len);
    zero_suffix = f->precision - frac_len - zero_prefix;
    if (zero_suffix > 0)
	f->floatzero = zero_suffix;
    return (total_len);
}

int rz_ftoa(char *buf, t_rz_arg *f, long double n)
{
    long integer;
    unsigned long frac;
    int buf_len;

    if (n < 0)
	f->negative = 1;
    frac = rz_modfl(n, f->precision, &integer);
    buf_len = rz_ltoa(buf, f, integer);
    if (f->precision > 0 || f->sharp)
	buf[buf_len++] = '.';
    if (f->precision > 0)
	buf_len += rz_ftoa_frac(buf + buf_len, f, frac);
    buf[buf_len] = '\0';
    return (buf_len);
}
