#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
#include "libft/libft.h"

enum va_conv_type {va_i, va_u, va_l, va_ul, va_c, va_cs};
enum arg_len_type {orig, flag_hh, flag_h, flag_l, flag_ll};
enum int_num_type {flag_dec, flag_oct, flag_hex, flag_Hex, flag_p};
struct arg_info
{
  enum va_conv_type va_conv;
  enum arg_len_type arg_len;
  enum int_num_type int_num;
  int fmt_len;
};

static enum va_conv_type parse_va_conv_type(const char *p, enum arg_len_type len)
{
  if (len == flag_hh || len == flag_h)
    return (*p == 'd' || *p == 'i') ? va_i : va_u;
  else if (len == flag_l || len == flag_ll)
    return (*p == 'd' || *p == 'i') ? va_l : va_ul;
  else if (*p == 'd' || *p == 'i')
    return va_i;
  else if (*p == 'u' || *p == 'o' || *p == 'x' || *p == 'X')
    return va_u;
  else if (*p == 's')
    return va_cs;
  else if (*p == 'p')
    return va_ul;
  else if (*p == 'c')
    return va_c;
  return va_i;
}

static enum int_num_type parse_arg_len_type(const char **s)
{
  const char *p;
  enum arg_len_type t;

  t = orig;
  p = *s;
  if (*p == 'h')
    t = p[1] == 'h' ? flag_hh : flag_h;
  else if (*p == 'l')
    t = p[1] == 'l' ? flag_ll : flag_l;
  if (t == flag_h || t == flag_l)
    (*s)++;
  else if (t == flag_hh || t == flag_ll)
    (*s) += 2;
  return t;
}

static enum int_num_type parse_int_num_type(const char *s)
{
  if (*s == 'o')
    return flag_oct;
  else if (*s == 'x')
    return flag_hex;
  else if (*s == 'X')
    return flag_Hex;
  else if (*s == 'p')
    return flag_p;
  else
    return flag_dec;
}

static int print_long_arg(struct arg_info *info, long arg)
{
  char *s;
  int result;

  if (info->arg_len == flag_hh)
    s = rz_ltoa((signed char)arg);
  else if (info->arg_len == flag_h)
    s = rz_ltoa((short)arg);
  else
    s = rz_ltoa(arg);
  result = rz_write(0, s, ft_strlen(s));
  free(s);
  return result;
}

static int print_ulong_arg(struct arg_info *info, unsigned long arg)
{
  char *s;
  int result;

  if (info->arg_len == flag_hh)
    {
      if (info->int_num == flag_oct)
	s = rz_otoa((unsigned char)arg);
      else if (info->int_num == flag_hex)
	s = rz_xtoa((unsigned char)arg);
      else if (info->int_num == flag_Hex)
	s = rz_Xtoa((unsigned char)arg);
      else
	s = rz_ultoa((unsigned char)arg);
    }
  else if (info->arg_len == flag_h)
    {
      if (info->int_num == flag_oct)
	s = rz_otoa((unsigned short)arg);
      else if (info->int_num == flag_hex)
	s = rz_xtoa((unsigned short)arg);
      else if (info->int_num == flag_Hex)
	s = rz_Xtoa((unsigned short)arg);
      else
	s = rz_ultoa((unsigned short)arg);
    }
  else
    {
      if (info->int_num == flag_oct)
	s = rz_otoa(arg);
      else if (info->int_num == flag_hex)
	s = rz_xtoa(arg);
      else if (info->int_num == flag_Hex)
	s = rz_Xtoa(arg);
      else if (info->int_num == flag_p)
	s = rz_ptoa(arg);
      else
	s = rz_ultoa(arg);
    }
  result = rz_write(0, s, ft_strlen(s));
  free(s);
  return result;
}

static struct arg_info parse_arg(const char **p)
{
  const char *base;
  struct arg_info info;

  base = *p;
  info.arg_len = parse_arg_len_type(p);
  info.va_conv = parse_va_conv_type(*p, info.arg_len);
  info.int_num = parse_int_num_type(*p);
  info.fmt_len = *p - base + 1;
  (*p)++;
  
  return info;
}

static int print_cstring_arg(const struct arg_info *info, const char *arg)
{
  (void) info;
  if (*arg == '\0')
    return 0;
  return rz_write(0, arg, ft_strlen(arg));
}

int ft_printf(const char *f, ...)
{
  struct arg_info info;
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
	  if (*f == '%')
	    result += rz_write(0, f++, 1);
	  else
	    {
	      info = parse_arg(&f);
	      if (info.va_conv == va_i)
		result += print_long_arg(&info, va_arg(ap, int));
	      else if (info.va_conv == va_u)
		result += print_ulong_arg(&info, va_arg(ap, unsigned int));
	      else if (info.va_conv == va_l)
		result += print_long_arg(&info, va_arg(ap, long));
	      else if (info.va_conv == va_ul)
		result += print_ulong_arg(&info, va_arg(ap, unsigned long));
	      else if (info.va_conv == va_c)
		{
		  char ch = va_arg(ap, unsigned int);
		  result += rz_write(0, &ch, 1);
		}
	      else if (info.va_conv == va_cs)
		result += print_cstring_arg(&info, va_arg(ap, const char *));
	    }
	}
    }
  va_end(ap);
  return result;
}
