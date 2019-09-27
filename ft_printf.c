#include <stdarg.h>
#include "ft_printf.h"
#include "rz_printf_impl.h"
#include "libft/libft.h"

static int is_signed_type(enum rz_arg_type f)
{
  return f == type_d || f == type_i || f == type_p || f == type_f;
}

static int is_unsigned_type(enum rz_arg_type f)
{
  return f == type_u || f == type_o || f == type_x || f == type_X;
}

static int is_number_type(enum rz_arg_type f)
{
  return is_signed_type(f) || is_unsigned_type(f);
}

static enum rz_cast_type select_rz_cast_type(const struct rz_arg *info)
{
  if (info->size == size_hh || info->size == size_h)
    return (info->type == type_d || info->type == type_i) ? cast_i : cast_u;
  else if ((info->size == size_l || info->size == size_ll) && info->type != type_f)
    return (info->type == type_d || info->type == type_i) ? cast_l : cast_ul;
  else if (info->type == type_d || info->type == type_i)
    return cast_i;
  else if (info->type == type_u || info->type == type_o ||
	   info->type == type_x || info->type == type_X || info->type == type_c)
    return cast_u;
  else if (info->type == type_s || info->type == type_p)
    return cast_ul;
  else if (info->type == type_percent)
    return cast_percent;
  else if (info->type == type_f)
    return (info->size == size_L) ? cast_long_double : cast_double;
  return cast_i;
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

static enum rz_arg_type parse_arg_type(const char *p)
{
  if (*p == 'c')
    return type_c;
  else if (*p == 's')
    return type_s;
  else if (*p == 'p')
    return type_p;
  else if (*p == 'd')
    return type_d;
  else if (*p == 'u')
    return type_u;
  else if (*p == 'o')
    return type_o;
  else if (*p == 'x')
    return type_x;
  else if (*p == 'X')
    return type_X;
  else if (*p == '%')
    return type_percent;
  else if (*p == 'f')
    return type_f;
  return type_d;
}

static void parse_flags(struct rz_arg *info, const char **p)
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

static void parse_fmt(struct rz_arg *info, const char **p)
{
  ft_memset(info, 0, sizeof *info);
  if (**p != '%')
    info->cast = cast_none;
  else
    {
      (*p)++;
      parse_flags(info, p);
      info->width = read_number(p);
      info->precision = parse_arg_precision(p);
      info->size = parse_arg_size(p);
      info->type = parse_arg_type(*p);
      info->cast = select_rz_cast_type(info);
      (*p)++;
    }
}

static void print_pad(struct rz_buf *buf, struct rz_arg *info)
{
  char ch;
  int total;

  ch = (!info->minus && info->zero) ? '0' : ' ';
  total = info->slen;
  if (info->precision >= 0 && info->type == type_s && info->precision < info->slen)
    total = info->precision;
  if (info->negative || (info->plus && is_signed_type(info->type)))
    total++;
  if (info->type == type_p ||
      (info->sharp && (info->type == type_x || info->type == type_X)))
    total += 2;
  else if (info->type == type_o && info->sharp)
    total++;
  if (info->negative && ch == '0')
    rz_buf_add(buf, "-", 1);
  if (info->width > total)
    rz_buf_fill(buf, ch, info->width - total);
}

static void print_prefix_arg(struct rz_buf *buf, struct rz_arg *info)
{
  if (is_signed_type(info->type) && !info->zero)
    {
      if (info->negative)
	rz_buf_add(buf, "-", 1);
      else if (info->plus)
	rz_buf_add(buf, "+", 1);
      else if (info->space)
	rz_buf_add(buf, " ", 1);
    }
  if (info->type == type_p ||
      (info->sharp && (info->type == type_x || info->type == type_X)))
    rz_buf_add(buf, info->type != type_X ? "0x" : "0X", 2);
  else if (info->sharp && info->type == type_o)
    rz_buf_add(buf, "0", 1);
}

static void print_type_arg(struct rz_buf *buf, struct rz_arg *info, const char *arg)
{
  int total;

  total = info->slen;
  if (info->type == type_s && info->precision >= 0 && info->precision < info->slen)
    total = info->precision;
  else if (is_number_type(info->type))
    {
      if (info->negative)
	arg++;
      if (info->precision > info->slen)
	rz_buf_fill(buf, '0', info->precision - info->slen);
    }
  rz_buf_add(buf, arg, total);
}

static void print_arg(struct rz_buf *buf, struct rz_arg *info, const char *arg)
{
  if (*arg == '\0')
    return;
  info->slen = ft_strlen(arg);
  if (info->negative)
    info->slen--;
  if (!info->minus)
    print_pad(buf, info);
  print_prefix_arg(buf, info);
  print_type_arg(buf, info, arg);
  if (info->minus)
    print_pad(buf, info);
}

static void print_long_arg(struct rz_buf *buf, struct rz_arg *info, long arg)
{
  char str[21];
  
  if (info->size == size_hh)
    rz_ltoa(str, (signed char)arg);
  else if (info->size == size_h)
    rz_ltoa(str, (short)arg);
  else
    rz_ltoa(str, arg);
  info->negative = arg < 0;
  print_arg(buf, info, str);
}

static void print_long_double_arg(struct rz_buf *buf, struct rz_arg *info, long double arg)
{
  char str[42];

  if (info->precision < 0)
    info->precision = 6;
  if (info->size == size_L)
    rz_ftoa(str, info, arg);
  else
    rz_ftoa(str, info, (double) arg);
  info->negative = arg < 0;
  info->precision = -1;
  print_arg(buf, info, str);
}

static void print_char(struct rz_buf *buf, struct rz_arg *info, char ch)
{
  char str[2];

  str[0] = ch;
  str[1] = '\0';
  info->negative = 0;
  print_arg(buf, info, str);
}

static void print_ulong_arg(struct rz_buf *buf, struct rz_arg *info, unsigned long arg)
{
  char str[21];

  info->negative = 0;
  if (info->type == type_c)
    print_char(buf, info, arg);
  else if (info->type == type_s)
    print_arg(buf, info, (const char *)arg);
  else
    {
      if (info->size == size_hh)
	rz_ultoa(str, (unsigned char)arg, info->type);
      else if (info->size == size_h)
	rz_ultoa(str, (unsigned short)arg, info->type);
      else
	rz_ultoa(str, arg, info->type);
      print_arg(buf, info, str);
    }
}

static void print_fmt(struct rz_buf *buf, struct rz_arg *info, const char **s)
{
  const char *p;

  p = *s;
  if (info->cast == cast_percent)
    rz_buf_add(buf, "%", 1);
  else
    {
      while (*p && *p != '%')
	p++;
      rz_buf_add(buf, *s, p - *s);
    }
  *s = p;
}

static void rz_printf_impl(struct rz_buf *buf, const char *f, va_list ap)
{
  struct rz_arg info;

  while (*f != '\0')
    {
      parse_fmt(&info, &f);
      if (info.cast == cast_none || info.cast == cast_percent)
	print_fmt(buf, &info, &f);
      else if (info.cast == cast_i)
	print_long_arg(buf, &info, va_arg(ap, int));
      else if (info.cast == cast_u)
	print_ulong_arg(buf, &info, va_arg(ap, unsigned int));
      else if (info.cast == cast_l)
	print_long_arg(buf, &info, va_arg(ap, long));
      else if (info.cast == cast_ul)
	print_ulong_arg(buf, &info, va_arg(ap, unsigned long));
      else if (info.cast == cast_double)
	print_long_double_arg(buf, &info, va_arg(ap, double));
      else if (info.cast == cast_long_double)
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
  rz_printf_impl(&buf, f, ap);
  rz_buf_flush(&buf);
  va_end(ap);
  return (buf.total);
}
