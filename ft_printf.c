#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
  if (!format)
    return -1;
  else if (*format == '\0')
    return 0;
  const char *p = format;
  while (*p != '\0')
    p++;
  return rz_write(0, format, p - format);
}
