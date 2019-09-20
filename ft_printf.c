#include "ft_printf.h"
#include "libft/libft.h"

int	ft_printf(const char *format, ...)
{
  if (!format)
    return -1;
  else if (*format == '\0')
    return 0;
  return rz_write(0, format, ft_strlen(format));
}
