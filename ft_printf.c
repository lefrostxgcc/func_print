#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
#include "libft/libft.h"

enum va_conv_type {va_none, va_percent, va_i, va_u, va_l, va_ul};
enum flag_type {f_c, f_s, f_p, f_d, f_i, f_u, f_o, f_x, f_X, f_percent,
		f_hh, f_h, f_l, f_ll};
struct arg_info
{
  enum va_conv_type va_conv;
  enum flag_type size;
  enum flag_type core;
  int fmt_len;
  int total_len;
};

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
      info->size = parse_arg_size(p);
      info->core = parse_arg_core(*p);
      info->va_conv = select_va_conv_type(info);
      info->fmt_len = *p - base + 1;
      (*p)++;
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
  info->total_len += rz_write(0, s, ft_strlen(s));
  free(s);
}

static void print_char(struct arg_info *info, char ch)
{
  info->total_len += rz_write(0, &ch, 1);
}

static void print_cstring_arg(struct arg_info *info, const char *arg)
{
  if (*arg == '\0')
    return;
  info->total_len += rz_write(0, arg, ft_strlen(arg));
}

static void print_ulong_arg(struct arg_info *info, unsigned long arg)
{
  char *s;

  if (info->core == f_c)
    {
      print_char(info, arg);
      return;
    }
  if (info->core == f_s)
    {
      print_cstring_arg(info, (const char *)arg);
      return;
    }
  if (info->size == f_hh)
    {
      if (info->core == f_o)
	s = rz_otoa((unsigned char)arg);
      else if (info->core == f_x)
	s = rz_xtoa((unsigned char)arg);
      else if (info->core == f_X)
	s = rz_Xtoa((unsigned char)arg);
      else
	s = rz_ultoa((unsigned char)arg);
    }
  else if (info->size == f_h)
    {
      if (info->core == f_o)
	s = rz_otoa((unsigned short)arg);
      else if (info->core == f_x)
	s = rz_xtoa((unsigned short)arg);
      else if (info->core == f_X)
	s = rz_Xtoa((unsigned short)arg);
      else
	s = rz_ultoa((unsigned short)arg);
    }
  else
    {
      if (info->core == f_o)
	s = rz_otoa(arg);
      else if (info->core == f_x)
	s = rz_xtoa(arg);
      else if (info->core == f_X)
	s = rz_Xtoa(arg);
      else if (info->core == f_p)
	s = rz_ptoa(arg);
      else
	s = rz_ultoa(arg);
    }
  info->total_len += rz_write(0, s, ft_strlen(s));
  free(s);
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
