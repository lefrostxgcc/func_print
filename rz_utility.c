#include "rz_printf.h"
#include "libft/libft.h"

int rz_ternary(int expression, int a, int b)
{
    if (expression)
	return (a);
    else
	return (b);
}

int rz_signed(t_rz_arg_type t)
{
    return (t == type_d || t == type_i || t == type_p || t == type_f);
}

int rz_unsigned(t_rz_arg_type t)
{
    return (t == type_u || t == type_o || t == type_x || t == type_X);
}

int rz_number(t_rz_arg_type t)
{
    return (rz_signed(t) || rz_unsigned(t));
}

int rz_read_integer_number(const char **s)
{
    const char *start;
    const char *end;
    int number;

    number = 0;
    start = *s;
    end = start;
    while (ft_isdigit(*end))
	end++;
    if (start == end)
      return (-1);
    *s = end;
    while (start < end)
    {
	number = number * 10 + (*start - '0');
	start++;
    }
    return (number);
}
