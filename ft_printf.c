#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
  (void) format;
  return rz_write(0, "Hello", 5);
}
