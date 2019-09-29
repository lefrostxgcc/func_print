#include "rz_printf.h"
#include "libft/libft.h"

long rz_tern_l(int expression, long a, long b)
{
    if (expression)
	return (a);
    else
	return (b);
}

void *rz_tern_p(int expression, void *a, void *b)
{
    if (expression)
	return (a);
    else
	return (b);
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
