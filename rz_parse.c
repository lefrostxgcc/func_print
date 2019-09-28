#include "rz_printf.h"
#include "libft/libft.h"

static t_rz_arg_size rz_read_arg_size(const char **fmt)
{
    const char *p;
    t_rz_arg_size size;

    size = size_none;
    p = *fmt;
    if (*p == 'h')
	size = rz_ternary(p[1] == 'h', size_hh, size_h);
    else if (*p == 'l')
	size = rz_ternary(p[1] == 'l', size_ll, size_l);
    else if (*p == 'L')
	size = size_L;
    if (size == size_h || size == size_l || size == size_L)
	(*fmt)++;
    else if (size == size_hh || size == size_ll)
	(*fmt) += 2;
    return (size);
}

static int rz_read_arg_precision(const char **fmt)
{
    int precision;
  
    if (**fmt != '.')
	return (-1);
    (*fmt)++;
    precision = rz_read_integer_number(fmt);
    if (precision == -1)
	return (0);
    else
	return (precision);
}

static t_rz_arg_type rz_read_arg_type(const char *fmt)
{
    if (*fmt == 'c')
	return (type_c);
    else if (*fmt == 's')
	return (type_s);
    else if (*fmt == 'p')
	return (type_p);
    else if (*fmt == 'd')
	return (type_d);
    else if (*fmt == 'u')
	return (type_u);
    else if (*fmt == 'o')
	return (type_o);
    else if (*fmt == 'x')
	return (type_x);
    else if (*fmt == 'X')
	return (type_X);
    else if (*fmt == '%')
	return (type_percent);
    else if (*fmt == 'f')
	return (type_f);
    else if (*fmt == 'i')
	return (type_i);
    return (type_none);
}

static void rz_read_flags(t_rz_arg *f, const char **fmt)
{
    while (**fmt)
    {
	if (**fmt == '-')
	    f->minus = 1;
	else if (**fmt == '#')
	    f->sharp = 1;
	else if (**fmt == '+')
	    f->plus = 1;
	else if (**fmt == '0')
	    f->zero = 1;
	else if (**fmt == ' ')
	    f->space = 1;
	else
	    return;
	(*fmt)++;
    }
}

void rz_parse_fmt(t_rz_buf *buf, t_rz_arg *f, const char **fmt)
{
    const char *percent;
  
    ft_memset(f, 0, sizeof *f);
    f->cast = cast_none;
    if (**fmt != '%')
      return;
    percent = *fmt;
    (*fmt)++;
    rz_read_flags(f, fmt);
    f->width = rz_read_integer_number(fmt);
    f->precision = rz_read_arg_precision(fmt);
    f->size = rz_read_arg_size(fmt);
    f->type = rz_read_arg_type(*fmt);
    f->cast = rz_select_cast(f);
    f->fmtlen = *fmt - percent - 1;
    (*fmt)++;
    if (f->type == type_none)
    {
	if (f->fmtlen > 0)
	    (*fmt) = percent;
	else
	{
	    (*fmt)--;
	    buf->total = -1;
	}
    }
}
