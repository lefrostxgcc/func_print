#include "rz_printf.h"
#include "libft/libft.h"

static void print_pad(t_rz_buf *buf, t_rz_arg *f)
{
    char ch;
    int total;

    ch = (!f->minus && f->zero && f->precision < 0) ? '0' : ' ';
    total = f->slen;
    if (f->precision >= 0 && f->type == type_s && f->precision < f->slen)
	total = f->precision;
    if (f->precision > f->slen && f->type != type_s)
	total = f->precision;
    if (f->negative || (f->plus && rz_signed(f->type)))
	total++;
    if (f->type == type_p ||
	(f->sharp && (f->type == type_x || f->type == type_X) &&
	 !f->argzero))
	total += 2;
    else if (f->type == type_o && f->sharp && !f->argzero)
	total++;
    if (f->negative && ch == '0')
	rz_buf_add(buf, "-", 1);
    if (f->width > total)
	rz_buf_fill(buf, ch, f->width - total);
}

static void print_prefix_arg(t_rz_buf *buf, t_rz_arg *f)
{
    if (rz_signed(f->type) && (!f->zero || f->precision > f->slen))
    {
	if (f->negative)
	    rz_buf_add(buf, "-", 1);
	else if (f->plus)
	    rz_buf_add(buf, "+", 1);
	else if (f->space)
	    rz_buf_add(buf, " ", 1);
    }
    if (f->type == type_p ||
	(f->sharp && (f->type == type_x || f->type == type_X) &&
	 !f->argzero))
	rz_buf_add(buf, f->type != type_X ? "0x" : "0X", 2);
    else if (f->sharp && f->type == type_o && !f->argzero)
	rz_buf_add(buf, "0", 1);
}

static void print_type_arg(t_rz_buf *buf, t_rz_arg *f, const char *arg)
{
    int total;

    total = f->slen;
    if (f->type == type_s && f->precision >= 0 && f->precision < f->slen)
	total = f->precision;
    else if (rz_number(f->type))
    {
	if (f->negative)
	    arg++;
	if (f->type != type_f && f->precision > f->slen)
	    rz_buf_fill(buf, '0', f->precision - f->slen);
    }
    rz_buf_add(buf, arg, total);
    if (f->type == type_f && f->floatzero > 0)
      rz_buf_fill(buf, '0', f->floatzero);
}

void rz_print_type_s(t_rz_buf *buf, t_rz_arg *f, const char *s)
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

void print_arg(t_rz_buf *buf, t_rz_arg *f, const char *arg)
{
    if (*arg == '\0')
	return;
    if (f->type == type_s)
	rz_print_type_s(buf, f, arg);
    else if (f->type == type_u)
	rz_print_type_u(buf, f, arg);
    else if (f->type == type_o)
	rz_print_type_o(buf, f, arg);
    else if (f->type == type_x || f->type == type_X)
	rz_print_type_xX(buf, f, arg);
    else if (f->type == type_p)
	rz_print_type_p(buf, f, arg);
    else
    {
	if (f->negative)
	    f->slen--;
	if (!f->minus)
	    print_pad(buf, f);
	print_prefix_arg(buf, f);
	print_type_arg(buf, f, arg);
	if (f->minus)
	    print_pad(buf, f);
    }
}
