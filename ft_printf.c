#include <stdarg.h>
#include "ft_printf.h"
#include "rz_printf_impl.h"
#include "libft/libft.h"

static int is_signed_core_flag(enum flag_type f)
{
  return f == f_d || f == f_i || f == f_p || f == f_f;
}

static int is_unsigned_core_flag(enum flag_type f)
{
  return f == f_u || f == f_o || f == f_x || f == f_X;
}

static int is_number_core_flag(enum flag_type f)
{
  return is_signed_core_flag(f) || is_unsigned_core_flag(f);
}

static enum va_conv_type select_va_conv_type(const struct arg_info *info)
{
  if (info->size == size_hh || info->size == size_h)
    return (info->core == f_d || info->core == f_i) ? va_i : va_u;
  else if ((info->size == size_l || info->size == size_ll) && info->core != f_f)
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
  else if (info->core == f_f)
    return (info->size == size_L) ? va_long_double : va_double;
  return va_i;
}

static enum rz_arg_size parse_arg_size(const char **s)
{
  const char *p;
  enum rz_arg_size t;

  t = size_none;
  p = *s;
  if (*p == 'h')
    t = p[1] == 'h' ? size_hh : size_h;
  else if (*p == 'l')
    t = p[1] == 'l' ? size_ll : size_l;
  else if (*p == 'L')
    t = size_L;
  if (t == size_h || t == size_l || t == size_L)
    (*s)++;
  else if (t == size_hh || t == size_ll)
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
  if (start == end)
    return -1;
  while (start < end)
    {
      number = number * 10 + (*start - '0');
      start++;
    }
  return number;
}

static int parse_arg_precision(const char **s)
{
  int precision;
  
  if (**s != '.')
    return -1;
  (*s)++;
  precision = read_number(s);
  return precision == -1 ? 0 : precision;
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
  else if (*p == 'f')
    return f_f;
  return f_d;
}

static void parse_flags(struct arg_info *info, const char **p)
{
  while (**p)
    {
      if (**p == '-')
	info->minus = 1;
      else if (**p == '#')
	info->sharp = 1;
      else if (**p == '+')
	info->plus = 1;
      else if (**p == '0')
	info->zero = 1;
      else if (**p == ' ')
	info->space = 1;
      else
	return;
      (*p)++;
    }
}

static void parse_fmt(struct arg_info *info, const char **p)
{
  const char *base;

  ft_memset(info, 0, sizeof *info);
  if (**p != '%')
    info->va_conv = va_none;
  else
    {
      (*p)++;
      base = *p;
      parse_flags(info, p);
      info->width = read_number(p);
      info->precision = parse_arg_precision(p);
      info->size = parse_arg_size(p);
      info->core = parse_arg_core(*p);
      info->va_conv = select_va_conv_type(info);
      info->fmt_len = *p - base + 1;
      (*p)++;
    }
}

static void print_pad(struct rz_buf *buf, struct arg_info *info)
{
  char ch;
  int total;

  ch = (!info->minus && info->zero) ? '0' : ' ';
  total = info->arg_len;
  if (info->precision >= 0 && info->core == f_s && info->precision < info->arg_len)
    total = info->precision;
  if (info->is_negative || (info->plus && is_signed_core_flag(info->core)))
    total++;
  if (info->core == f_p ||
      (info->sharp && (info->core == f_x || info->core == f_X)))
    total += 2;
  else if (info->core == f_o && info->sharp)
    total++;
  if (info->is_negative && ch == '0')
    rz_buf_add(buf, "-", 1);
  if (info->width > total)
    rz_buf_fill(buf, ch, info->width - total);
}

static void print_prefix_arg(struct rz_buf *buf, struct arg_info *info)
{
  if (is_signed_core_flag(info->core) && !info->zero)
    {
      if (info->is_negative)
	rz_buf_add(buf, "-", 1);
      else if (info->plus)
	rz_buf_add(buf, "+", 1);
      else if (info->space)
	rz_buf_add(buf, " ", 1);
    }
  if (info->core == f_p ||
      (info->sharp && (info->core == f_x || info->core == f_X)))
    rz_buf_add(buf, info->core != f_X ? "0x" : "0X", 2);
  else if (info->sharp && info->core == f_o)
    rz_buf_add(buf, "0", 1);
}

static void print_core_arg(struct rz_buf *buf, struct arg_info *info, const char *arg)
{
  int total;

  total = info->arg_len;
  if (info->core == f_s && info->precision >= 0 && info->precision < info->arg_len)
    total = info->precision;
  else if (is_number_core_flag(info->core))
    {
      if (info->is_negative)
	arg++;
      if (info->precision > info->arg_len)
	rz_buf_fill(buf, '0', info->precision - info->arg_len);
    }
  rz_buf_add(buf, arg, total);
}

static void print_arg(struct rz_buf *buf, struct arg_info *info, const char *arg)
{
  if (*arg == '\0')
    return;
  info->arg_len = ft_strlen(arg);
  if (info->is_negative)
    info->arg_len--;
  if (!info->minus)
    print_pad(buf, info);
  print_prefix_arg(buf, info);
  print_core_arg(buf, info, arg);
  if (info->minus)
    print_pad(buf, info);
}

static void print_long_arg(struct rz_buf *buf, struct arg_info *info, long arg)
{
  char str[21];
  
  if (info->size == size_hh)
    rz_ltoa(str, (signed char)arg);
  else if (info->size == size_h)
    rz_ltoa(str, (short)arg);
  else
    rz_ltoa(str, arg);
  info->is_negative = arg < 0;
  print_arg(buf, info, str);
}

static void print_long_double_arg(struct rz_buf *buf, struct arg_info *info, long double arg)
{
  char str[42];

  if (info->precision < 0)
    info->precision = 6;
  if (info->size == size_L)
    rz_ftoa(str, info, arg);
  else
    rz_ftoa(str, info, (double) arg);
  info->is_negative = arg < 0;
  info->precision = -1;
  print_arg(buf, info, str);
}

static void print_char(struct rz_buf *buf, struct arg_info *info, char ch)
{
  char str[2];

  str[0] = ch;
  str[1] = '\0';
  info->is_negative = 0;
  print_arg(buf, info, str);
}

static void print_ulong_arg(struct rz_buf *buf, struct arg_info *info, unsigned long arg)
{
  char str[21];

  info->is_negative = 0;
  if (info->core == f_c)
    print_char(buf, info, arg);
  else if (info->core == f_s)
    print_arg(buf, info, (const char *)arg);
  else
    {
      if (info->size == size_hh)
	rz_ultoa(str, (unsigned char)arg, info->core);
      else if (info->size == size_h)
	rz_ultoa(str, (unsigned short)arg, info->core);
      else
	rz_ultoa(str, arg, info->core);
      print_arg(buf, info, str);
    }
}

static void print_fmt(struct rz_buf *buf, struct arg_info *info, const char **s)
{
  const char *p;

  p = *s;
  if (info->va_conv == va_percent)
    rz_buf_add(buf, "%", 1);
  else
    {
      while (*p && *p != '%')
	p++;
      rz_buf_add(buf, *s, p - *s);
    }
  *s = p;
}

static void ft_printf_impl(struct rz_buf *buf, const char *f, va_list ap)
{
  struct arg_info info;

  while (*f != '\0')
    {
      parse_fmt(&info, &f);
      if (info.va_conv == va_none || info.va_conv == va_percent)
	print_fmt(buf, &info, &f);
      else if (info.va_conv == va_i)
	print_long_arg(buf, &info, va_arg(ap, int));
      else if (info.va_conv == va_u)
	print_ulong_arg(buf, &info, va_arg(ap, unsigned int));
      else if (info.va_conv == va_l)
	print_long_arg(buf, &info, va_arg(ap, long));
      else if (info.va_conv == va_ul)
	print_ulong_arg(buf, &info, va_arg(ap, unsigned long));
      else if (info.va_conv == va_double)
	print_long_double_arg(buf, &info, va_arg(ap, double));
      else if (info.va_conv == va_long_double)
	print_long_double_arg(buf, &info, va_arg(ap, long double));
    }
}

int ft_printf(const char *f, ...)
{
  struct rz_buf buf;
  va_list ap;

  if (!f)
    return (-1);
  buf.pos = buf.total = 0;
  va_start(ap, f);
  ft_printf_impl(&buf, f, ap);
  rz_buf_flush(&buf);
  va_end(ap);
  return (buf.total);
}
