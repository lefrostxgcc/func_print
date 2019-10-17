#include "rz_printf.h"

static long rz_ext(long double n, int p, unsigned long *l, unsigned long *h)
{
    long i;
    unsigned long pl_pow;
    unsigned long ph_pow;
    int tp;
    long double tn;

    i = n;
    n -= i;
    *h = 0;
    if (n < 0)
	n = -n;
    tp = p;
    if (p > 18)
	p = 18;
    pl_pow = rz_pow(10, p);
    n *= pl_pow;
    *l = n;
    n -= *l;
    if (tp > 18)
    {
	p = tp - 18;
	if (p > 18)
	    p = 18;
	ph_pow = rz_pow(10, p);
	n *= ph_pow;
	*h = n;
	tn = n - (unsigned long) n;
	tn *= 10;
	if (((unsigned long) tn) % 10 >= 5)
	    (*h)++;
	if (*h >= ph_pow)
	{
	    *h = 0;
	    (*l)++;
	    if (*l >= pl_pow)
	    {
		i += rz_tern_l(i > 0, 1, -1);
		*l = 0;
	    }
	}
    }
    else
    {
	tn = n - (unsigned long) n;
	tn *= 10;
	if (((unsigned long) tn) % 10 >= 5)
	    (*l)++;
	if (*l >= pl_pow)
	{
	    i += rz_tern_l(i > 0, 1, -1);
	    *l = 0;
	    *h = 0;
	}
    }
    return (i);
}

static int rz_ftoa_f(char *buf, t_rz_arg *f, unsigned long l, unsigned long h)
{
    char lrep[21];
    char hrep[21];
    int zero_prefix;
    int zero_suffix;
    int total_len;
    int l_len;
    int h_len;

    zero_prefix = 0;
    lrep[0] = '\0';
    hrep[0] = '\0';
    l_len = rz_ultoa(lrep, f, l);
    h_len = h > 0 ? rz_ultoa(hrep, f, h) : 0;
    total_len = l_len + h_len;
    if (f->precision > total_len)
    {
	zero_prefix = f->precision - total_len;
	rz_memset(buf, '0', zero_prefix);
	total_len += zero_prefix;
    }
    rz_memcpy(buf + zero_prefix, lrep, l_len);
    rz_memcpy(buf + zero_prefix + l_len, hrep, h_len);
    zero_suffix = f->precision - l_len - h_len - zero_prefix;
    if (zero_suffix > 0)
	f->floatzero = zero_suffix;
    return (total_len);
}

int rz_ftoa(char *buf, t_rz_arg *f, long double n)
{
    long integer;
    unsigned long l;
    unsigned long h;
    int buf_len;

    if (n < 0)
	f->negative = 1;
    integer = rz_ext(n, f->precision, &l, &h);
    buf_len = rz_ltoa(buf, f, integer);
    if (f->precision > 0 || f->sharp)
	buf[buf_len++] = '.';
    if (f->precision > 0)
	buf_len += rz_ftoa_f(buf + buf_len, f, l, h);
    buf[buf_len] = '\0';
    return (buf_len);
}
