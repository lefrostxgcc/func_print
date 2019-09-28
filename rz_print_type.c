#include "rz_printf.h"
#include "libft/libft.h"

void print_long_arg(t_rz_buf *buf, t_rz_arg *f, long arg)
{
    char str[21];
  
    if (f->size == size_hh)
	rz_ltoa(str, (signed char)arg);
    else if (f->size == size_h)
	rz_ltoa(str, (short)arg);
    else
	rz_ltoa(str, arg);
    f->negative = arg < 0;
    print_arg(buf, f, str);
}

void print_long_double_arg(t_rz_buf *buf, t_rz_arg *f, long double arg)
{
    char str[42];

    if (f->precision < 0)
	f->precision = 6;
    if (f->size == size_L)
	rz_ftoa(str, f, arg);
    else
	rz_ftoa(str, f, (double) arg);
    f->negative = arg < 0;
    f->precision = -1;
    print_arg(buf, f, str);
}

void print_char(t_rz_buf *buf, t_rz_arg *f, char ch)
{
    char str[2];

    str[0] = ch;
    str[1] = '\0';
    f->negative = 0;
    print_arg(buf, f, str);
}

void print_ulong_arg(t_rz_buf *buf, t_rz_arg *f, unsigned long arg)
{
    char str[21];

    f->negative = 0;
    if (f->type == type_c)
	print_char(buf, f, arg);
    else if (f->type == type_s)
	print_arg(buf, f, (const char *)arg);
    else
    {
	if (f->size == size_hh)
	    rz_ultoa(str, (unsigned char)arg, f->type);
	else if (f->size == size_h)
	    rz_ultoa(str, (unsigned short)arg, f->type);
	else
	    rz_ultoa(str, arg, f->type);
	print_arg(buf, f, str);
    }
}

void print_fmt(t_rz_buf *buf, t_rz_arg *f, const char **s)
{
    const char *p;

    p = *s;
    if (f->cast == cast_percent)
	rz_buf_add(buf, "%", 1);
    else
    {
	while (*p && *p != '%')
	    p++;
	rz_buf_add(buf, *s, p - *s);
    }
    *s = p;
}
