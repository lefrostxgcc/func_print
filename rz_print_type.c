#include "rz_printf.h"
#include "libft/libft.h"

void rz_print_as_long(t_rz_buf *buf, t_rz_arg *f, long a)
{
    char str_rep[21];
  
    if (f->size == size_hh)
	f->slen = rz_ltoa(str_rep, f, (signed char) a);
    else if (f->size == size_h)
	f->slen = rz_ltoa(str_rep, f, (short) a);
    else
	f->slen = rz_ltoa(str_rep, f, a);
    rz_print_type(buf, f, str_rep);
}

void rz_print_as_ldouble(t_rz_buf *buf, t_rz_arg *f, long double a)
{
    char str_rep[42];

    if (f->precision < 0)
	f->precision = 6;
    if (f->size == size_L)
	f->slen = rz_ftoa(str_rep, f, a);
    else
	f->slen = rz_ftoa(str_rep, f, (double) a);
    f->negative = a < 0;
    f->precision = -1;
    rz_print_type(buf, f, str_rep);
}

void rz_print_as_ulong(t_rz_buf *buf, t_rz_arg *f, unsigned long a)
{
    char str_rep[21];
    const char *s;

    s = str_rep;
    if (f->type == type_s)
    {
	s = (const char *) a;
	f->slen = ft_strlen(s);
    }
    else if (f->type == type_c)
    {
	str_rep[0] = a;
	str_rep[1] = '\0';
	f->slen = 1;
    }
    else
    {
	f->argzero = (a == 0);
	if (f->size == size_hh)
	    f->slen = rz_ultoa(str_rep, (unsigned char) a, f->type);
	else if (f->size == size_h)
	    f->slen = rz_ultoa(str_rep, (unsigned short) a, f->type);
	else
	    f->slen = rz_ultoa(str_rep, a, f->type);
    }
    rz_print_type(buf, f, s);
}

void rz_print_type(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    if (s == 0 || *s == '\0')
	return;
    if (f->negative)
    {
	f->slen--;
	s++;
    }
    if (f->type == type_c || f->type == type_s)
	rz_print_type_cs(buf, f, s);
    else if (f->type == type_u)
	rz_print_type_u(buf, f, s);
    else if (f->type == type_o)
	rz_print_type_o(buf, f, s);
    else if (f->type == type_x || f->type == type_X || f->type == type_p)
	rz_print_type_xp(buf, f, s);
    else if (f->type == type_d || f->type == type_i || f->type == type_f)
	rz_print_type_dif(buf, f, s);
}

void rz_print_fmt(t_rz_buf *buf, t_rz_arg *f, const char **fmt)
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
