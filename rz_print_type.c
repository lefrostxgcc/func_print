#include "rz_printf.h"

void print_long_arg(t_rz_buf *buf, t_rz_arg *f, long arg)
{
    char str_rep[21];
  
    if (f->size == size_hh)
	rz_ltoa(str_rep, (signed char) arg);
    else if (f->size == size_h)
	rz_ltoa(str_rep, (short) arg);
    else
	rz_ltoa(str_rep, arg);
    f->negative = arg < 0;
    print_arg(buf, f, str_rep);
}

void print_long_double_arg(t_rz_buf *buf, t_rz_arg *f, long double arg)
{
    char str_rep[42];

    if (f->precision < 0)
	f->precision = 6;
    if (f->size == size_L)
	rz_ftoa(str_rep, f, arg);
    else
	rz_ftoa(str_rep, f, (double) arg);
    f->negative = arg < 0;
    print_arg(buf, f, str_rep);
}

void print_ulong_arg(t_rz_buf *buf, t_rz_arg *f, unsigned long arg)
{
    char str_rep[21];
    const char *s;

    f->negative = 0;
    if (f->type == type_s)
	s = (const char *) arg;
    else if (f->type == type_c)
    {
	str_rep[0] = arg;
	str_rep[1] = '\0';
	s = str_rep;
    }
    else
    {
	if (f->size == size_hh)
	    rz_ultoa(str_rep, (unsigned char) arg, f->type);
	else if (f->size == size_h)
	    rz_ultoa(str_rep, (unsigned short) arg, f->type);
	else
	    rz_ultoa(str_rep, arg, f->type);
	s = str_rep;
    }
    print_arg(buf, f, s);
}

void print_fmt(t_rz_buf *buf, t_rz_arg *f, const char **fmt)
{
    const char *p;

    if (f->cast == cast_percent)
	rz_buf_add(buf, "%", 1);
    else
    {
	p = *fmt;
	while (*p && *p != '%')
	    p++;
	rz_buf_add(buf, *fmt, p - *fmt);
	*fmt = p;
    }
}
