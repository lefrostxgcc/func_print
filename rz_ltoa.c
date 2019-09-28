#include "rz_printf.h"
#include "libft/libft.h"

static unsigned rz_type_base(t_rz_arg_type type)
{
    if (type == type_o)
	return (8);
    else if (type == type_x || type == type_X || type == type_p)
	return (16);
    return (10);
}

static char rz_digit_to_char(int n, t_rz_arg_type type)
{
    if (n < 10)
	return (n + '0');
    else if (type == type_X)
	return (n - 10 + 'A');
    else
	return (n - 10 + 'a');
}

static int rz_digit_count(unsigned long n, unsigned base)
{
    int count;

    count = 1;
    while (n > base - 1)
    {
	n /= base;
	count++;
    }
    return (count);
}

int rz_ultoa(char *buf, unsigned long n, t_rz_arg_type type)
{
    int base;
    int buf_len;

    base = rz_type_base(type);
    buf_len = rz_digit_count(n, base);
    buf[0] = '0';
    buf += buf_len;
    *buf-- = '\0';
    while (n != 0)
    {
	*buf-- = rz_digit_to_char(n % base, type);
	n /= base;
    }
    return (buf_len);
}

int rz_ltoa(char *buf, long n)
{
    int buf_len;
    
    if (n == (long) 0x8000000000000000L)
    {
	buf[0] = '\0';
	ft_strcpy(buf, "-9223372036854775808");
	return (sizeof ("-9223372036854775808"));
    }
    buf_len = 0;
    if (n < 0)
    {
	n = -n;
	buf[0] = '-';
	buf++;
	buf_len++;
    }
    buf_len += rz_ultoa(buf, n, type_d);
    return (buf_len);
}
