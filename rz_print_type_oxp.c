#include "rz_printf.h"

static void rz_print_x_zero(t_rz_buf *buf, t_rz_arg *f, char ch)
{
    int padding;

    if (f->precision == 0)
	rz_buf_fill(buf, ' ', rz_tern_l(f->width > 0, f->width, 0));
    else if(f->precision > 0)
    {
	padding = f->width - f->precision;
	if (padding > 0 && !f->minus)
	    rz_buf_fill(buf, ' ', padding);
	rz_buf_fill(buf, '0', f->precision);
	if (padding > 0 && f->minus)
	    rz_buf_fill(buf, ' ', padding);
    }
    else
    {
	padding = f->width - 1;
	if (padding > 0 && !f->minus)
	    rz_buf_fill(buf, ch, padding);
	rz_buf_fill(buf, '0', 1);
	if (padding > 0 && f->minus)
	    rz_buf_fill(buf, ' ', padding);
    }
}

void rz_print_type_x(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int width;
    int padding;

    ch = rz_tern_l(!f->minus && f->zero && f->precision < 0, '0', ' ');
    if (f->argzero)
	rz_print_x_zero(buf, f, ch);
    else
    {
	width = rz_tern_l(f->precision > f->slen, f->precision, f->slen);
	if (f->sharp)
	    width += 2;
	padding = f->width - width;
	if (ch == ' ' && !f->minus && padding > 0)
	    rz_buf_fill(buf, ch, padding);
	if (f->sharp)
	    rz_buf_add(buf, rz_tern_p(f->type == type_X, "0X", "0x"), 2);
	if (ch == ' ' && f->precision > f->slen)
	    rz_buf_fill(buf, '0', f->precision - f->slen);
	else if (ch == '0')
	    rz_buf_fill(buf, '0', padding);
	rz_buf_add(buf, s, f->slen);
	if (f->minus && padding > 0)
	    rz_buf_fill(buf, ' ', padding);
    }
}

void rz_print_type_p(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int width;
    int padding;

    ch = rz_tern_l(!f->minus && f->zero && f->precision < 0, '0', ' ');
    width = rz_tern_l(f->precision > f->slen, f->precision, f->slen);
    if (!f->argzero)
	width += 2;
    padding = f->width - width;
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (!f->argzero)
	rz_buf_add(buf, "0x", 2);
    if (f->precision > f->slen && !f->argzero)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    if (f->sharp || !(f->precision == 0 && f->argzero) || f->argzero)
	rz_buf_add(buf, s, f->slen);
    if (f->minus && padding > 0)
	rz_buf_fill(buf, ' ', padding);
}

void rz_print_type_o(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int width;
    int padding;

    ch = rz_tern_l(!f->minus && f->zero && f->precision < 0, '0', ' ');
    width = rz_tern_l(f->precision > f->slen, f->precision, f->slen);
    if (f->argzero && f->precision == 0 && f->width > 0 && !f->sharp)
	width--;
    if (f->sharp && !f->argzero && f->precision <= f->slen)
	width++;
    padding = f->width - width;
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (f->sharp && !f->argzero && f->precision <= f->slen)
	rz_buf_add(buf, "0", 1);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    if (f->sharp || !(f->precision == 0 && f->argzero))
	rz_buf_add(buf, s, f->slen);
    if (f->minus && padding > 0)
	rz_buf_fill(buf, ' ', padding);
}
