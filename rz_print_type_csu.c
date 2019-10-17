#include "rz_printf.h"

void rz_print_type_c(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    int width;
    int spaces;

    width = f->slen;
    spaces = f->width - width;
    if (!f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
    rz_buf_add(buf, s, width);
    if (f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
}

void rz_print_type_s(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    int width;
    int spaces;

    if (f->precision >= 0 && f->precision < f->slen)
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

    if (!f->minus && f->zero && f->precision < 0)
	ch = '0';
    else
	ch = ' ';
    if (f->precision > f->slen)
	width = f->precision;
    else
	width = f->slen;
    if (f->argzero && f->precision == 0 && f->width > 0)
	width--;
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

void rz_print_percent(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    int width;
    int spaces;
    char ch;

    if (!f->minus && f->zero)
	ch = '0';
    else
	ch = ' ';
    width = f->slen;
    spaces = f->width - width;
    if (!f->minus && spaces > 0)
	rz_buf_fill(buf, ch, spaces);
    rz_buf_add(buf, s, width);
    if (f->minus && spaces > 0)
	rz_buf_fill(buf, ' ', spaces);
}
