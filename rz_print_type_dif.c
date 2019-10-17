#include "rz_printf.h"

static void rz_print_sign_placeholder(t_rz_buf *buf, t_rz_arg *f)
{
    if (f->negative)
	rz_buf_add(buf, "-", 1);
    else if (f->plus)
	rz_buf_add(buf, "+", 1);
    else if (f->space)
	rz_buf_add(buf, " ", 1);
}

void rz_print_type_di(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    char ch;
    int width;
    int padding;

    ch = rz_tern_l(!f->minus && f->zero && f->precision < 0, '0', ' ');
    width = rz_tern_l(f->precision > f->slen, f->precision, f->slen);
    if (f->negative || f->plus || f->space)
	width++;
    if (f->argzero && f->precision == 0 && f->width > 0)
	width--;
    padding = f->width - width;
    if (ch == '0')
	rz_print_sign_placeholder(buf, f);
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (ch != '0')
	rz_print_sign_placeholder(buf, f);
    if (f->precision > f->slen)
	rz_buf_fill(buf, '0', f->precision - f->slen);
    if (!(f->precision == 0 && f->argzero))
	rz_buf_add(buf, s, f->slen);
    if (f->minus && padding > 0)
	rz_buf_fill(buf, ' ', padding);
}

void rz_print_type_f(t_rz_buf *buf, t_rz_arg *f, const char *s)
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
    if (f->negative || f->plus || f->space)
	width++;
    padding = f->width - width;
    if (ch == '0')
	rz_print_sign_placeholder(buf, f);
    if (!f->minus && padding > 0)
	rz_buf_fill(buf, ch, padding);
    if (ch != '0')
	rz_print_sign_placeholder(buf, f);
    rz_buf_add(buf, s, f->slen);
    if (f->minus && padding > 0)
	rz_buf_fill(buf, ' ', padding);
}
