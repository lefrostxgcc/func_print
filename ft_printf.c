#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
#include "libft/libft.h"

int ft_printf(const char *format, ...)
{
  if (!format)
    return -1;
  else if (*format == '\0')
    return 0;
  va_list ap;
  va_start(ap, format);
  if (format[0] == '%')
    {
      if (format[1] == 'c')
	{
	  char ch = va_arg(ap, int);
	  return rz_write(0, &ch, 1);
	}
      else if (format[1] == 's')
	{
	  const char *p = va_arg(ap, const char *);
	  if (*p == '\0')
	      return 0;
	  return rz_write(0, p, ft_strlen(p));
	}
      else if (format[1] == '%')
	{
	  return rz_write(0, "%", 1);
	}
      else if (format[1] == 'd' || format[1] == 'i')
	{
	  int a = va_arg(ap, int);
	  char *p = rz_ltoa(a);
	  int result = rz_write(0, p, ft_strlen(p));
	  free(p);
	  return result;
	}
      else if (format[1] == 'u')
	{
	  unsigned int a = va_arg(ap, unsigned int);
	  char *p = rz_ultoa(a);
	  int result = rz_write(0, p, ft_strlen(p));
	  free(p);
	  return result;
	}
      else if (format[1] == 'h')
	{
	  if (format[2] == 'h')
	    {
	      if (format[3] == 'd' || format[3] == 'i')
		{
		  int a = va_arg(ap, int);
		  char *p = rz_ltoa((char)a);
		  int result = rz_write(0, p, ft_strlen(p));
		  free(p);
		  return result;
		}
	      else if (format[3] == 'u')
		{
		  unsigned int a = va_arg(ap, unsigned int);
		  char *p = rz_ultoa((unsigned char)a);
		  int result = rz_write(0, p, ft_strlen(p));
		  free(p);
		  return result;
		}
	    }
	  else if (format[2] == 'd' || format[2] == 'i')
	    {
	      int a = va_arg(ap, int);
	      char *p = rz_ltoa((short)a);
	      int result = rz_write(0, p, ft_strlen(p));
	      free(p);
	      return result;
	    }
	  else if (format[2] == 'u')
	    {
	      unsigned int a = va_arg(ap, unsigned int);
	      char *p = rz_ultoa((unsigned short)a);
	      int result = rz_write(0, p, ft_strlen(p));
	      free(p);
	      return result;
	    }
	}
      else if (format[1] == 'l')
	{
	  if (format[2] == 'd' || format[2] == 'i')
	    {
	      long a = va_arg(ap, long);
	      char *p = rz_ltoa(a);
	      int result = rz_write(0, p, ft_strlen(p));
	      free(p);
	      return result;
	    }
	  else if (format[2] == 'u')
	    {
	      unsigned long a = va_arg(ap, unsigned long);
	      char *p = rz_ultoa(a);
	      int result = rz_write(0, p, ft_strlen(p));
	      free(p);
	      return result;
	    }
	  else if (format[2] == 'l')
	    {
	      if (format[3] == 'd' || format[3] == 'i')
		{
		  long a = va_arg(ap, long);
		  char *p = rz_ltoa(a);
		  int result = rz_write(0, p, ft_strlen(p));
		  free(p);
		  return result;
		}
	      else if (format[3] == 'u')
		{
		  unsigned long a = va_arg(ap, unsigned long);
		  char *p = rz_ultoa(a);
		  int result = rz_write(0, p, ft_strlen(p));
		  free(p);
		  return result;
		}
	    }
	}
    }
  va_end(ap);
  return rz_write(0, format, ft_strlen(format));
}
