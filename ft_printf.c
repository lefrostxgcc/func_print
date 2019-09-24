#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
#include "libft/libft.h"

static int is_number_core_flag(enum flag_type f)
{
  return f == f_d || f == f_i || f == f_u || f == f_o ||
    f == f_x || f == f_X;
}

static enum va_conv_type select_va_conv_type(const struct arg_info *info)
{
  if (info->size == f_hh || info->size == f_h)
    return (info->core == f_d || info->core == f_i) ? va_i : va_u;
  else if (info->size == f_l || info->size == f_ll)
    return (info->core == f_d || info->core == f_i) ? va_l : va_ul;
  else if (info->core == f_d || info->core == f_i)
    return va_i;
  else if (info->core == f_u || info->core == f_o ||
	   info->core == f_x || info->core == f_X || info->core == f_c)
    return va_u;
  else if (info->core == f_s || info->core == f_p)
    return va_ul;
  else if (info->core == f_percent)
    return va_percent;
  return va_i;
}

static enum flag_type parse_arg_size(const char **s)
{
  const char *p;
  enum flag_type t;

  t = f_d;
  p = *s;
  if (*p == 'h')
    t = p[1] == 'h' ? f_hh : f_h;
  else if (*p == 'l')
    t = p[1] == 'l' ? f_ll : f_l;
  if (t == f_h || t == f_l)
    (*s)++;
  else if (t == f_hh || t == f_ll)
    (*s) += 2;
  return t;
}

static int read_number(const char **s)
{
  const char *start;
  const char *end;
  int number;

  number = 0;
  start = end = *s;
  while (ft_isdigit(*end))
    end++;
  *s = end;
  while (start < end)
    {
      number = number * 10 + (*start - '0');
      start++;
    }
  return number;
}

static int parse_arg_width(const char **s)
{
  return read_number(s);
}

static int parse_arg_precision(const char **s)
{
  if (**s != '.')
    return -1;
  (*s)++;
  return read_number(s);
}

static enum flag_type parse_arg_core(const char *p)
{
  if (*p == 'c')
    return f_c;
  else if (*p == 's')
    return f_s;
  else if (*p == 'p')
    return f_p;
  else if (*p == 'd')
    return f_d;
  else if (*p == 'u')
    return f_u;
  else if (*p == 'o')
    return f_o;
  else if (*p == 'x')
    return f_x;
  else if (*p == 'X')
    return f_X;
  else if (*p == '%')
    return f_percent;
  return f_d;
}

static void parse_fmt(struct arg_info *info, const char **p)
{
  const char *base;

  if (**p != '%')
    info->va_conv = va_none;
  else
    {
      (*p)++;
      base = *p;
      info->width = parse_arg_width(p);
      info->precision = parse_arg_precision(p);
      info->size = parse_arg_size(p);
      info->core = parse_arg_core(*p);
      info->va_conv = select_va_conv_type(info);
      info->fmt_len = *p - base + 1;
      (*p)++;
    }
}

static void print_arg(struct arg_info *info, const char *arg)
{
  char *s;
  int len;

  if (*arg == '\0')
    return;
  len = ft_strlen(arg);
  if (info->core == f_s && info->precision < len && info->precision != -1)
    {
      info->total_len += rz_write(0, arg, info->precision);
    }
  else if (is_number_core_flag(info->core) && info->precision > len)
    {
      if (*arg == '-')
	{
	  s = (char *) malloc(sizeof (char) * (info->precision + 2));
	  ft_memset(s, '0', info->precision + 1);
	  s[0] = '-';
	  ft_strcpy(s + (info->precision - len + 1) + 1, arg + 1);
	  info->total_len += rz_write(0, s, info->precision + 1);
	}
      else
	{
	  s = (char *) malloc(sizeof (char) * (info->precision + 1));
	  ft_memset(s, '0', info->precision);
	  ft_strcpy(s + (info->precision - len), arg);
	  info->total_len += rz_write(0, s, info->precision);
	}
      free(s);
    }
  else if (info->width > len)
    {
      s = (char *) malloc(sizeof (char) * (info->width + 1));
      ft_memset(s, ' ', info->width);
      ft_strcpy(s + (info->width - len), arg);
      info->total_len += rz_write(0, s, info->width);
      free(s);
    }
  else
    {
      info->total_len += rz_write(0, arg, len);
    }
}

static void print_long_arg(struct arg_info *info, long arg)
{
  char *s;

  if (info->size == f_hh)
    s = rz_ltoa((signed char)arg);
  else if (info->size == f_h)
    s = rz_ltoa((short)arg);
  else
    s = rz_ltoa(arg);
  print_arg(info, s);
  free(s);
}

static void print_char(struct arg_info *info, char ch)
{
  char buf[2];

  buf[0] = ch;
  buf[1] = '\0';
  print_arg(info, buf);
}

static void print_ulong_arg(struct arg_info *info, unsigned long arg)
{
  char *s;

  if (info->core == f_c)
    print_char(info, arg);
  else if (info->core == f_s)
    print_arg(info, (const char *)arg);
  else
    {
      if (info->size == f_hh)
	s = rz_ultoa((unsigned char)arg, info->core);
      else if (info->size == f_h)
	s = rz_ultoa((unsigned short)arg, info->core);
      else
	s = rz_ultoa(arg, info->core);
      print_arg(info, s);
      free(s);
    }
}

static void print_fmt(struct arg_info *info, const char **s)
{
  const char *p;

  p = *s;
  if (info->va_conv == va_percent)
    print_char(info, '%');
  else
    {
      while (*p && *p != '%')
	p++;
      info->total_len += rz_write(0, *s, p - *s);
    }
  *s = p;
}

int ft_printf(const char *f, ...)
{
  struct arg_info info;
  va_list ap;

  if (!f)
    return -1;
  info.total_len = 0;
  va_start(ap, f);
  while (*f != '\0')
    {
      parse_fmt(&info, &f);
      if (info.va_conv == va_none || info.va_conv == va_percent)
	print_fmt(&info, &f);
      else if (info.va_conv == va_i)
	print_long_arg(&info, va_arg(ap, int));
      else if (info.va_conv == va_u)
	print_ulong_arg(&info, va_arg(ap, unsigned int));
      else if (info.va_conv == va_l)
	print_long_arg(&info, va_arg(ap, long));
      else if (info.va_conv == va_ul)
	print_ulong_arg(&info, va_arg(ap, unsigned long));
    }
  va_end(ap);
  return info.total_len;
}
