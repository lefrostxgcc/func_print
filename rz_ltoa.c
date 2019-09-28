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

void rz_ultoa(char *res, unsigned long n, t_rz_arg_type type)
{
    int base;

    base = rz_type_base(type);
    res[0] = '0';
    res += rz_digit_count(n, base);
    *res-- = '\0';
    while (n != 0)
    {
	*res-- = rz_digit_to_char(n % base, type);
	n /= base;
    }
}

void rz_ltoa(char *res, long n)
{
    if (n == (long) 0x8000000000000000L)
    {
	res[0] = '\0';
	ft_strcpy(res, "-9223372036854775808");
	return;
    }
    if (n < 0)
    {
	n = -n;
	res[0] = '-';
	res++;
    }
    rz_ultoa(res, n, type_d);
}
