#include <stdarg.h>
#include "ft_printf.h"
#include "libft/libft.h"

int ft_printf(const char *format, ...)
{
  if (!format)
    return -1;
  else if (*format == '\0')
    return 0;
  va_list ap;
  va_start(ap, format);
  char ch = va_arg(ap, int);
  va_end(ap);
  if (ch == 'a')
    return rz_write(0, &ch, 1);
  return rz_write(0, format, ft_strlen(format));
}
