#include "rz_printf.h"

void rz_print_long(t_rz_buf *buf, t_rz_arg *f, long a)
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

void rz_print_ldouble(t_rz_buf *buf, t_rz_arg *f, long double a)
{
    char str_rep[64];

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

void rz_print_ulong(t_rz_buf *buf, t_rz_arg *f, unsigned long a)
{
    char str_rep[21];
    const char *s;

    s = str_rep;
    if (f->type == type_c)
    {
	str_rep[0] = a;
	str_rep[1] = '\0';
	f->slen = 1;
    }
    else
    {
	if (f->size == size_hh)
	    f->slen = rz_ultoa(str_rep, f, (unsigned char) a);
	else if (f->size == size_h)
	    f->slen = rz_ultoa(str_rep, f, (unsigned short) a);
	else
	    f->slen = rz_ultoa(str_rep, f, a);
    }
    rz_print_type(buf, f, s);
}

void rz_print_type(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    if ((s == 0 || f->slen <= 0) && f->width < 0)
	return;
    if (f->negative)
    {
	f->slen--;
	s++;
    }
    if (f->type == type_c)
	rz_print_type_c(buf, f, s);
    else if (f->type == type_s)
	rz_print_type_s(buf, f, s);
    else if (f->type == type_u)
	rz_print_type_u(buf, f, s);
    else if (f->type == type_o)
	rz_print_type_o(buf, f, s);
    else if (f->type == type_x || f->type == type_X)
	rz_print_type_x(buf, f, s);
    else if (f->type == type_p)
	rz_print_type_p(buf, f, s);
    else if (f->type == type_d || f->type == type_i)
	rz_print_type_di(buf, f, s);
    else if (f->type == type_f)
	rz_print_type_f(buf, f, s);
    else if (f->type == type_percent)
	rz_print_percent(buf, f, s);
}
