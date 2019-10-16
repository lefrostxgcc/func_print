#include <stdarg.h>
#include "ft_printf.h"
#include "rz_printf.h"

static void rz_printf(t_rz_buf *buf, const char *fmt, va_list ap)
{
    t_rz_arg f;

    while (*fmt != '\0')
    {
	rz_parse_fmt(&f, &fmt);
	if (f.cast == cast_none || f.cast == cast_percent)
	    rz_print_fmt(buf, &f, &fmt);
	else if (f.cast == cast_i)
	    rz_print_long(buf, &f, va_arg(ap, int));
	else if (f.cast == cast_u)
	    rz_print_ulong(buf, &f, va_arg(ap, unsigned int));
	else if (f.cast == cast_l)
	    rz_print_long(buf, &f, va_arg(ap, long));
	else if (f.cast == cast_ul)
	    rz_print_ulong(buf, &f, va_arg(ap, unsigned long));
	else if (f.cast == cast_s)
	    rz_print_cstring(buf, &f, va_arg(ap, const char *));
	else if (f.cast == cast_p)
	    rz_print_pointer(buf, &f, va_arg(ap, void *));
	else if (f.cast == cast_double)
	    rz_print_ldouble(buf, &f, va_arg(ap, double));
	else if (f.cast == cast_long_double)
	    rz_print_ldouble(buf, &f, va_arg(ap, long double));
    }
}

int ft_printf(const char *fmt, ...)
{
    t_rz_buf buf;
    va_list ap;

    if (!fmt)
	return (-1);
    buf.pos = 0;
    buf.total = 0;
    va_start(ap, fmt);
    rz_printf(&buf, fmt, ap);
    rz_buf_flush(&buf);
    va_end(ap);
    return (buf.total);
}
