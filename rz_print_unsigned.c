#include "rz_printf.h"

void rz_print_type_cs(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    int width;
    int spaces;

    if (f->type == type_s && f->precision >= 0 && f->precision < f->slen)
	width = f->precision;
    else
	width = f->slen;
    spaces = f->width - width;
    if (!f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
    rz_buf_add(buf, s, width);
    if (f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
}

void rz_print_type_u(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int width;
    int padding;

    ch = rz_tern_l(!f->minus && f->zero && f->precision < 0, '0', ' ');
    width = rz_tern_l(f->precision > f->slen, f->precision, f->slen);
    padding = f->width - width;
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    if (!(f->precision == 0 && *s == '0'))
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
    if (f->sharp && !f->argzero)
	width++;
    padding = f->width - width;
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (f->sharp && !f->argzero)
	rz_buf_add(buf, "0", 1);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padding > 0)
	rz_buf_fill(buf, ' ', padding);
}

void rz_print_type_xp(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int width;
    int padding;

    ch = rz_tern_l(!f->minus && f->zero && f->precision < 0, '0', ' ');
    width = rz_tern_l(f->precision > f->slen, f->precision, f->slen);
    if (f->type == type_p || (f->sharp && !f->argzero))
	width += 2;
    padding = f->width - width;
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (f->type == type_p || (f->sharp && !f->argzero))
	rz_buf_add(buf, rz_tern_p(f->type == type_X, "0X", "0x"), 2);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    if (!(f->precision == 0 && *s == '0'))
	rz_buf_add(buf, s, f->slen);
    if (f->minus && padding > 0)
	rz_buf_fill(buf, ' ', padding);
}
