#include "rz_printf.h"

static int rz_low_prec(long double n, t_rz_frac *frac, int prec)
{
    unsigned long low_pow;
    
    frac->high = 0;
    low_pow = rz_pow(10, prec);
    n *= low_pow;
    frac->low = n;
    n -= frac->low;
    n *= 10;
    if (((unsigned long) n) % 10 >= 5)
	frac->low++;
    if (frac->low >= low_pow)
	return (1);
    return (0);
}

static int rz_high_prec(long double n, t_rz_frac *frac, int prec)
{
    unsigned long low_pow;
    unsigned long high_pow;

    if (prec > 36)
	prec = 36;
    low_pow = rz_pow(10, 18);
    n *= low_pow;
    frac->low = n;
    n -= frac->low;
    prec -= 18;
    high_pow = rz_pow(10, prec);
    n *= high_pow;
    frac->high = n;
    n *= 10;
    if (((unsigned long) n) % 10 >= 5)
	frac->high++;
    if (frac->high >= high_pow)
    {
	frac->high = 0;
	frac->low++;
	if (frac->low >= low_pow)
	    return (1);
    }
    return (0);
}

static long rz_modfl(long double n, t_rz_frac *frac, int prec)
{
    long integer;
    int need_round_integer;

    integer = (long) n;
    n -= integer;
    if (n < 0)
	n = -n;
    if (prec < 18)
	need_round_integer = rz_low_prec(n, frac, prec);
    else
	need_round_integer = rz_high_prec(n, frac, prec);
    if (need_round_integer)
    {
	integer += rz_tern_l(integer > 0, 1, -1);
	frac->low = 0;
	frac->high = 0;
    }
    return (integer);
}

static int rz_ftoa_frac(char *buf, t_rz_arg *f, t_rz_frac *frac)
{
    char s[42];
    int zero_prefix;
    int total_len;
    int low_len;
    int high_len;

    zero_prefix = 0;
    s[0] = '\0';
    s[21] = '\0';
    low_len = rz_ultoa(s, f, frac->low);
    high_len = 0;
    if (frac->high > 0)
	high_len = rz_ultoa(s + 21, f, frac->high);
    total_len = low_len + high_len;
    if (f->precision > total_len)
    {
	zero_prefix = f->precision - total_len;
	rz_memset(buf, '0', zero_prefix);
	total_len += zero_prefix;
    }
    rz_memcpy(buf + zero_prefix, s, low_len);
    rz_memcpy(buf + zero_prefix + low_len, s + 21, high_len);
    return (total_len);
}

int rz_ftoa(char *buf, t_rz_arg *f, long double n)
{
    t_rz_frac frac;
    long integer;
    int buf_len;

    if (n < 0)
	f->negative = 1;
    integer = rz_modfl(n, &frac, f->precision);
    buf_len = rz_ltoa(buf, f, integer);
    if (f->precision > 0 || f->sharp)
	buf[buf_len++] = '.';
    if (f->precision > 0)
	buf_len += rz_ftoa_frac(buf + buf_len, f, &frac);
    buf[buf_len] = '\0';
    return (buf_len);
}
