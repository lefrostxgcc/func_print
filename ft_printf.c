#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
#include "libft/libft.h"

enum {va_i, va_u, va_l, va_ul, va_cs, va_percent};

static int parse_va_arg_type(const char *p)
{
  if (*p == 'd' || *p == 'i')
    return va_i;
  else if (*p == 'u' || *p == 'c' || *p == 'o' || *p == 'x' || *p == 'X')
    return va_u;
  else if ((*p == 'h' && (p[1] == 'd' || p[1] == 'i')) ||
	   (*p == 'h' && p[1] == 'h' && (p[2] == 'd' || p[2] == 'i')))
    return va_i;
  else if ((*p == 'l' && (p[1] == 'd' || p[1] == 'i')) ||
	   (*p == 'l' && p[1] == 'l' && (p[2] == 'd' || p[2] == 'i')))
    return va_l;
  else if ((*p == 'h' && p[1] == 'u') ||
	   (*p == 'h' && p[1] == 'h' && p[2] == 'u'))
    return va_u;
  else if ((*p == 'h' && p[1] == 'o') ||
	   (*p == 'h' && p[1] == 'h' && p[2] == 'o'))
    return va_u;
  else if ((*p == 'h' && p[1] == 'x') ||
	   (*p == 'h' && p[1] == 'h' && p[2] == 'x'))
    return va_u;
  else if ((*p == 'h' && p[1] == 'X') ||
	   (*p == 'h' && p[1] == 'h' && p[2] == 'X'))
    return va_u;
  else if ((*p == 'l' && p[1] == 'u') ||
	   (*p == 'l' && p[1] == 'l' && p[2] == 'u'))
    return va_ul;
  else if ((*p == 'l' && p[1] == 'o') ||
	   (*p == 'l' && p[1] == 'l' && p[2] == 'o'))
    return va_ul;
  else if ((*p == 'l' && p[1] == 'x') ||
	   (*p == 'l' && p[1] == 'l' && p[2] == 'x'))
    return va_ul;
  else if ((*p == 'l' && p[1] == 'X') ||
	   (*p == 'l' && p[1] == 'l' && p[2] == 'X'))
    return va_ul;
  else if (*p == 'p')
    return va_ul;
  else if (*p == 's')
    return va_cs;
  else if (*p == '%')
    return va_percent;
  return va_i;
}

static int print_int_arg(const char **f, int arg)
{
  const char *p;
  char *s;
  int result;

  p = *f;
  if (*p == 'd' || *p == 'i')
    {
      s = rz_ltoa(arg);
      (*f)++;
    }
  else if (*p == 'h' && (p[1] == 'd' || p[1] == 'i'))
    {
      s = rz_ltoa((short)arg);
      (*f) += 2;
    }
  else if (*p == 'h' && p[1] == 'h' && (p[2] == 'd' || p[2] == 'i'))
    {
      s = rz_ltoa((signed char)arg);
      (*f) += 3;
    }
  result = rz_write(0, s, ft_strlen(s));
  free(s);
  return result;
}

static int print_uint_arg(const char **f, unsigned arg)
{
  const char *p;
  char *s;
  int result;

  p = *f;
  if (*p == 'u')
    {
      s = rz_ultoa(arg);
      (*f)++;
    }
  else if (*p == 'c')
    {
      char ch = (unsigned char) arg;
      (*f)++;
      return rz_write(0, &ch, 1);
    }
  else if (*p == 'o')
    {
      s = rz_otoa(arg);
      (*f)++;
    }
  else if (*p == 'x')
    {
      s = rz_xtoa(arg);
      (*f)++;
    }
  else if (*p == 'X')
    {
      s = rz_Xtoa(arg);
      (*f)++;
    }
  else if (*p == 'h' && p[1] == 'u')
    {
      s = rz_ultoa((unsigned short)arg);
      (*f) += 2;
    }
  else if (*p == 'h' && p[1] == 'o')
    {
      s = rz_otoa((unsigned short)arg);
      (*f) += 2;
    }
  else if (*p == 'h' && p[1] == 'x')
    {
      s = rz_xtoa((unsigned short)arg);
      (*f) += 2;
    }
  else if (*p == 'h' && p[1] == 'X')
    {
      s = rz_Xtoa((unsigned short)arg);
      (*f) += 2;
    }
  else if (*p == 'h' && p[1] == 'h' && p[2] == 'u')
    {
      s = rz_ultoa((unsigned char)arg);
      (*f) += 3;
    }
  else if (*p == 'h' && p[1] == 'h' && p[2] == 'o')
    {
      s = rz_otoa((unsigned char)arg);
      (*f) += 3;
    }
  else if (*p == 'h' && p[1] == 'h' && p[2] == 'x')
    {
      s = rz_xtoa((unsigned char)arg);
      (*f) += 3;
    }
  else if (*p == 'h' && p[1] == 'h' && p[2] == 'X')
    {
      s = rz_Xtoa((unsigned char)arg);
      (*f) += 3;
    }
  result = rz_write(0, s, ft_strlen(s));
  free(s);
  return result;
}

static int print_long_arg(const char **f, long arg)
{
  const char *p;
  char *s;
  int result;

  p = *f;
  if (*p == 'l' && (p[1] == 'd' || p[1] == 'i'))
    {
      s = rz_ltoa(arg);
      (*f) += 2;
    }
  else if (*p == 'l' && p[1] == 'l' && (p[2] == 'd' || p[2] == 'i'))
    {
      s = rz_ltoa(arg);
      (*f) += 3;
    }
  result = rz_write(0, s, ft_strlen(s));
  free(s);
  return result;
}

static int print_ulong_arg(const char **f, unsigned long arg)
{
  const char *p;
  char *s;
  int result;

  p = *f;
  if (*p == 'p')
    {
      s = rz_ptoa(arg);
      (*f)++;
    }
  else if (*p == 'l' && p[1] == 'u')
    {
      s = rz_ultoa(arg);
      (*f) += 2;
    }
  else if (*p == 'l' && p[1] == 'o')
    {
      s = rz_otoa(arg);
      (*f) += 2;
    }
  else if (*p == 'l' && p[1] == 'x')
    {
      s = rz_xtoa(arg);
      (*f) += 2;
    }
  else if (*p == 'l' && p[1] == 'X')
    {
      s = rz_Xtoa(arg);
      (*f) += 2;
    }
  else if (*p == 'l' && p[1] == 'l' && p[2] == 'u')
    {
      s = rz_ultoa(arg);
      (*f) += 3;
    }
  else if (*p == 'l' && p[1] == 'l' && p[2] == 'o')
    {
      s = rz_otoa(arg);
      (*f) += 3;
    }
  else if (*p == 'l' && p[1] == 'l' && p[2] == 'x')
    {
      s = rz_xtoa(arg);
      (*f) += 3;
    }
  else if (*p == 'l' && p[1] == 'l' && p[2] == 'X')
    {
      s = rz_Xtoa(arg);
      (*f) += 3;
    }
  result = rz_write(0, s, ft_strlen(s));
  free(s);
  return result;
}

static int print_cstring_arg(const char **f, const char *arg)
{
  (*f)++;
  if (*arg == '\0')
    return 0;
  return rz_write(0, arg, ft_strlen(arg));
}

int ft_printf(const char *f, ...)
{
  int arg_type;
  int result;
  va_list ap;

  result = f ? 0 : -1;
  if (!f)
    return -1;
  va_start(ap, f);
  while (*f != '\0')
    {
      if (*f != '%')
	result += rz_write(0, f++, 1);
      else
	{
	  f++;
	  arg_type = parse_va_arg_type(f);
	  if (arg_type == va_i)
	    result += print_int_arg(&f, va_arg(ap, int));
	  else if (arg_type == va_u)
	    result += print_uint_arg(&f, va_arg(ap, unsigned int));
	  else if (arg_type == va_l)
	    result += print_long_arg(&f, va_arg(ap, long));
	  else if (arg_type == va_ul)
	    result += print_ulong_arg(&f, va_arg(ap, unsigned long));
	  else if (arg_type == va_cs)
	    result += print_cstring_arg(&f, va_arg(ap, const char *));
	  else if (arg_type == va_percent)
	    result += rz_write(0, f++, 1);
	}
    }
  va_end(ap);
  return result;
}
