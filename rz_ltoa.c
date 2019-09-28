#include "rz_printf.h"
#include "libft/libft.h"

static unsigned flag_base(t_rz_arg_type flag)
{
    if (flag == type_o)
	return 8;
    else if (flag == type_x || flag == type_X || flag == type_p)
	return 16;
    return 10;
}

static char digit_char(unsigned long n, t_rz_arg_type type)
{
    if (n < 10)
	return n + '0';
    else
	return n - 10 + (type == type_X ? 'A' : 'a');
}

static int digit_count(unsigned long n, unsigned base)
{
    int i;

    i = 1;
    while (n > base - 1)
    {
	n = n / base;
	i++;
    }
    return (i);
}

void rz_ultoa(char *res, unsigned long n, t_rz_arg_type flag)
{
    int len;
    int base;

    base = flag_base(flag);
    len = digit_count(n, base);
    res += len;
    *res-- = '\0';
    while (--len)
    {
	*res-- = digit_char(n % base, flag);
	n = n / base;
    }
    *res = digit_char(n % base, flag);
}

void rz_ltoa(char *res, long n)
{
    int len;
    int sign;

    if (n == (long) 9223372036854775808UL)
    {
	res[0] = '\0';
	ft_strcpy(res, "-9223372036854775808");
	return;
    }
    if ((sign = n < 0 ? 1 : 0))
	n = -n;
    len = digit_count(n, 10);
    if (sign)
	len++;
    res += len;
    *res-- = '\0';
    while (--len)
    {
	*res-- = n % 10 + '0';
	n = n / 10;
    }
    if (sign)
	*res = '-';
    else
	*res = n + '0';
}
