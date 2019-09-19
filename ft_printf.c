#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
  (void) format;
  if (!format)
    return -1;
  const char *p = format;
  while (*p != '\0')
    p++;
  return rz_write(0, format, p - format);
}
