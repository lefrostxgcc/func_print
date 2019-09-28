#include <stdarg.h>
#include "ft_printf.h"
#include "rz_printf.h"
#include "libft/libft.h"

static int rz_signed(t_rz_arg_type t)
{
    return t == type_d || t == type_i || t == type_p || t == type_f;
}

static int rz_unsigned(t_rz_arg_type t)
{
    return t == type_u || t == type_o || t == type_x || t == type_X;
}

static int rz_number(t_rz_arg_type t)
{
    return rz_signed(t) || rz_unsigned(t);
}

static enum e_rz_cast_type rz_select_cast(const t_rz_arg *f)
{
    if (f->size == size_hh || f->size == size_h)
	return (f->type == type_d || f->type == type_i) ? cast_i : cast_u;
    else if ((f->size == size_l || f->size == size_ll) && f->type != type_f)
	return (f->type == type_d || f->type == type_i) ? cast_l : cast_ul;
    else if (f->type == type_d || f->type == type_i)
	return cast_i;
    else if (f->type == type_u || f->type == type_o ||
	     f->type == type_x || f->type == type_X || f->type == type_c)
	return cast_u;
    else if (f->type == type_s || f->type == type_p)
	return cast_ul;
    else if (f->type == type_percent)
	return cast_percent;
    else if (f->type == type_f)
	return (f->size == size_L) ? cast_long_double : cast_double;
    return cast_i;
}

static t_rz_arg_size rz_read_arg_size(const char **s)
{
    const char *p;
    t_rz_arg_size size;

    size = size_none;
    p = *s;
    if (*p == 'h')
	size = p[1] == 'h' ? size_hh : size_h;
    else if (*p == 'l')
	size = p[1] == 'l' ? size_ll : size_l;
    else if (*p == 'L')
	size = size_L;
    if (size == size_h || size == size_l || size == size_L)
	(*s)++;
    else if (size == size_hh || size == size_ll)
	(*s) += 2;
    return (size);
}

static int rz_read_integer_number(const char **s)
{
    const char *start;
    const char *end;
    int number;

    number = 0;
    start = end = *s;
    while (ft_isdigit(*end))
	end++;
    *s = end;
    if (start == end)
	return -1;
    while (start < end)
    {
	number = number * 10 + (*start - '0');
	start++;
    }
    return (number);
}

static int rz_read_arg_precision(const char **s)
{
    int precision;
  
    if (**s != '.')
	return -1;
    (*s)++;
    precision = rz_read_integer_number(s);
    return precision == -1 ? 0 : precision;
}

static t_rz_arg_type rz_read_arg_type(const char *p)
{
    if (*p == 'c')
	return type_c;
    else if (*p == 's')
	return type_s;
    else if (*p == 'p')
	return type_p;
    else if (*p == 'd')
	return type_d;
    else if (*p == 'u')
	return type_u;
    else if (*p == 'o')
	return type_o;
    else if (*p == 'x')
	return type_x;
    else if (*p == 'X')
	return type_X;
    else if (*p == '%')
	return type_percent;
    else if (*p == 'f')
	return type_f;
    return type_d;
}

static void rz_read_flags(t_rz_arg *f, const char **p)
{
    while (**p)
    {
	if (**p == '-')
	    f->minus = 1;
	else if (**p == '#')
	    f->sharp = 1;
	else if (**p == '+')
	    f->plus = 1;
	else if (**p == '0')
	    f->zero = 1;
	else if (**p == ' ')
	    f->space = 1;
	else
	    return;
	(*p)++;
    }
}

static void parse_fmt(t_rz_arg *f, const char **p)
{
    ft_memset(f, 0, sizeof *f);
    if (**p != '%')
	f->cast = cast_none;
    else
    {
	(*p)++;
	rz_read_flags(f, p);
	f->width = rz_read_integer_number(p);
	f->precision = rz_read_arg_precision(p);
	f->size = rz_read_arg_size(p);
	f->type = rz_read_arg_type(*p);
	f->cast = rz_select_cast(f);
	(*p)++;
    }
}

static void print_pad(t_rz_buf *buf, t_rz_arg *f)
{
    char ch;
    int total;

    ch = (!f->minus && f->zero) ? '0' : ' ';
    total = f->slen;
    if (f->precision >= 0 && f->type == type_s && f->precision < f->slen)
	total = f->precision;
    if (f->negative || (f->plus && rz_signed(f->type)))
	total++;
    if (f->type == type_p ||
	(f->sharp && (f->type == type_x || f->type == type_X)))
	total += 2;
    else if (f->type == type_o && f->sharp)
	total++;
    if (f->negative && ch == '0')
	rz_buf_add(buf, "-", 1);
    if (f->width > total)
	rz_buf_fill(buf, ch, f->width - total);
}

static void print_prefix_arg(t_rz_buf *buf, t_rz_arg *f)
{
    if (rz_signed(f->type) && !f->zero)
    {
	if (f->negative)
	    rz_buf_add(buf, "-", 1);
	else if (f->plus)
	    rz_buf_add(buf, "+", 1);
	else if (f->space)
	    rz_buf_add(buf, " ", 1);
    }
    if (f->type == type_p ||
	(f->sharp && (f->type == type_x || f->type == type_X)))
	rz_buf_add(buf, f->type != type_X ? "0x" : "0X", 2);
    else if (f->sharp && f->type == type_o)
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
	if (f->precision > f->slen)
	    rz_buf_fill(buf, '0', f->precision - f->slen);
    }
    rz_buf_add(buf, arg, total);
}

static void print_arg(t_rz_buf *buf, t_rz_arg *f, const char *arg)
{
    if (*arg == '\0')
	return;
    f->slen = ft_strlen(arg);
    if (f->negative)
	f->slen--;
    if (!f->minus)
	print_pad(buf, f);
    print_prefix_arg(buf, f);
    print_type_arg(buf, f, arg);
    if (f->minus)
	print_pad(buf, f);
}

static void print_long_arg(t_rz_buf *buf, t_rz_arg *f, long arg)
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

static void print_long_double_arg(t_rz_buf *buf, t_rz_arg *f, long double arg)
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

static void print_char(t_rz_buf *buf, t_rz_arg *f, char ch)
{
    char str[2];

    str[0] = ch;
    str[1] = '\0';
    f->negative = 0;
    print_arg(buf, f, str);
}

static void print_ulong_arg(t_rz_buf *buf, t_rz_arg *f, unsigned long arg)
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

static void print_fmt(t_rz_buf *buf, t_rz_arg *f, const char **s)
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

static void rz_printf(t_rz_buf *buf, const char *fmt, va_list ap)
{
    t_rz_arg f;

    while (*fmt != '\0')
    {
	parse_fmt(&f, &fmt);
	if (f.cast == cast_none || f.cast == cast_percent)
	    print_fmt(buf, &f, &fmt);
	else if (f.cast == cast_i)
	    print_long_arg(buf, &f, va_arg(ap, int));
	else if (f.cast == cast_u)
	    print_ulong_arg(buf, &f, va_arg(ap, unsigned int));
	else if (f.cast == cast_l)
	    print_long_arg(buf, &f, va_arg(ap, long));
	else if (f.cast == cast_ul)
	    print_ulong_arg(buf, &f, va_arg(ap, unsigned long));
	else if (f.cast == cast_double)
	    print_long_double_arg(buf, &f, va_arg(ap, double));
	else if (f.cast == cast_long_double)
	    print_long_double_arg(buf, &f, va_arg(ap, long double));
    }
}

int ft_printf(const char *fmt, ...)
{
    t_rz_buf buf;
    va_list ap;

    if (!fmt)
	return (-1);
    buf.pos = buf.total = 0;
    va_start(ap, fmt);
    rz_printf(&buf, fmt, ap);
    rz_buf_flush(&buf);
    va_end(ap);
    return (buf.total);
}
