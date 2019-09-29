#include "rz_printf.h"
#include "libft/libft.h"

void rz_print_type_cs(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    int total;
    int spaces;

    if (f->precision >= 0 && f->precision < f->slen)
	total = f->precision;
    else
	total = f->slen;
    spaces = f->width - total;
    if (!f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
    rz_buf_add(buf, s, total);
    if (f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
}

void rz_print_type_u(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int total;
    int padcount;

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->precision > f->slen)
	total = f->precision;
    else
	total = f->slen;
    padcount = f->width - total;
    if (!f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
}

void rz_print_type_o(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int total;
    int padcount;

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->precision > f->slen)
	total = f->precision;
    else
	total = f->slen;
    if (f->sharp && !f->argzero)
	total++;
    padcount = f->width - total;
    if (!f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
    if (f->sharp && !f->argzero)
	rz_buf_add(buf, "0", 1);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
}

void rz_print_type_xX(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int total;
    int padcount;

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->precision > f->slen)
	total = f->precision;
    else
	total = f->slen;
    if (f->sharp && !f->argzero)
	total += 2;
    padcount = f->width - total;
    if (!f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
    if (f->sharp && !f->argzero)
    {
	if (f->type == type_x)
	    rz_buf_add(buf, "0x", 2);
	else
	    rz_buf_add(buf, "0X", 2);
    }
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
}

void rz_print_type_p(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int total;
    int padcount;

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->precision > f->slen)
	total = f->precision;
    else
	total = f->slen;
    total += 2;
    padcount = f->width - total;
    if (!f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
    rz_buf_add(buf, "0x", 2);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
}

void rz_print_type_di(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int total;
    int padcount;

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->negative)
    {
	s++;
	f->slen--;
    }
    if (f->precision > f->slen)
	total = f->precision;
    else
	total = f->slen;
    if (f->negative || f->plus || f->space)
	total++;
    padcount = f->width - total;
    if (ch == '0')
    {
	if (f->negative)
	    rz_buf_add(buf, "-", 1);
	else if (f->plus)
	    rz_buf_add(buf, "+", 1);
	else if (f->space)
	    rz_buf_add(buf, " ", 1);
    }
    if (!f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
    if (ch != '0')
    {
	if (f->negative)
	    rz_buf_add(buf, "-", 1);
	else if (f->plus)
	    rz_buf_add(buf, "+", 1);
	else if (f->space)
	    rz_buf_add(buf, " ", 1);
    }
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
}

void rz_print_type_f(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int total;
    int padcount;

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->negative)
    {
	s++;
	f->slen--;
    }
    total = f->slen;
    if (f->negative || f->plus || f->space)
	total++;
    padcount = f->width - total;
    if (ch == '0')
    {
	if (f->negative)
	    rz_buf_add(buf, "-", 1);
	else if (f->plus)
	    rz_buf_add(buf, "+", 1);
	else if (f->space)
	    rz_buf_add(buf, " ", 1);
    }
    if (!f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
    if (ch != '0')
    {
	if (f->negative)
	    rz_buf_add(buf, "-", 1);
	else if (f->plus)
	    rz_buf_add(buf, "+", 1);
	else if (f->space)
	    rz_buf_add(buf, " ", 1);
    }
    rz_buf_add(buf, s, f->slen);
    if (f->floatzero > 0)
	rz_buf_fill(buf, '0', f->floatzero);
    if (f->minus && padcount > 0)
	rz_buf_fill(buf, ch, padcount);
}

void print_arg(t_rz_buf *buf, t_rz_arg *f, const char *arg)
{
    if (*arg == '\0')
	return;
    if (f->type == type_c || f->type == type_s)
	rz_print_type_cs(buf, f, arg);
    else if (f->type == type_u)
	rz_print_type_u(buf, f, arg);
    else if (f->type == type_o)
	rz_print_type_o(buf, f, arg);
    else if (f->type == type_x || f->type == type_X)
	rz_print_type_xX(buf, f, arg);
    else if (f->type == type_p)
	rz_print_type_p(buf, f, arg);
    else if (f->type == type_d || f->type == type_i)
	rz_print_type_di(buf, f, arg);
    else if (f->type == type_f)
	rz_print_type_f(buf, f, arg);
}
