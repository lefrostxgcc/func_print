#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
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
  else if (info->core == f_f)
    return va_double;
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
  if (start == end)
    return -1;
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
  int precision;
  
  if (**s != '.')
    return -1;
  (*s)++;
  precision = read_number(s);
  return precision == -1 ? 0 : precision;
}

static int parse_arg_minus(const char **s)
{
  if (**s == '-')
    {
      (*s)++;
      return 1;
    }
  else
    return 0;
}

static int parse_arg_plus(const char **s)
{
  if (**s == '+')
    {
      (*s)++;
      return 1;
    }
  else
    return 0;
}

static int parse_arg_pound(const char **s)
{
  if (**s == '#')
    {
      (*s)++;
      return 1;
    }
  else
    return 0;
}

static int parse_arg_zero(const char **s)
{
  if (**s == '0')
    {
      (*s)++;
      return 1;
    }
  else
    return 0;
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

static void parse_fmt(struct arg_info *info, const char **p)
{
  const char *base;

  if (**p != '%')
    info->va_conv = va_none;
  else
    {
      (*p)++;
      base = *p;
      info->has_minus = parse_arg_minus(p);
      info->has_plus = parse_arg_plus(p);
      info->has_pound = parse_arg_pound(p);
      info->has_zero = parse_arg_zero(p);
      info->width = parse_arg_width(p);
      info->precision = parse_arg_precision(p);
      info->size = parse_arg_size(p);
      info->core = parse_arg_core(*p);
      info->va_conv = select_va_conv_type(info);
      info->fmt_len = *p - base + 1;
      (*p)++;
    }
}

static void flush_buf(struct rz_buffer *buf)
{
  buf->total += rz_write(0, buf->data, buf->pos);
  buf->pos = 0;
}

static void fill_buf(struct rz_buffer *buf, char ch, int count)
{
  int b_left;

  while (count > 0)
    {
      b_left = (sizeof (buf->data)) - buf->pos;
      if (count > b_left)
	{
	  count -= b_left;
	  ft_memset(buf->data + buf->pos, ch, b_left);
	  flush_buf(buf);
	}
      else
	{
	  ft_memset(buf->data + buf->pos, ch, count);
	  buf->pos += count;
	  count = 0;
	}
    }
}

static void print_to_buf(struct rz_buffer *buf, const char *s, int s_len)
{
  int s_pos;
  int b_left;
  int s_left;

  s_pos = 0;
  while (s_pos < s_len)
    {
      b_left = (sizeof (buf->data)) - buf->pos;
      s_left = s_len - s_pos;
      if (s_left > b_left)
	{
	  s_left -= b_left;
	  ft_memcpy(buf->data + buf->pos, s + s_pos, b_left);
	  flush_buf(buf);
	  s_pos += b_left;
	}
      else
	{
	  ft_memcpy(buf->data + buf->pos, s + s_pos, s_left);
	  buf->pos += s_left;
	  s_pos += s_left;
	}
    }
}

static void print_pad(struct rz_buffer *buf, struct arg_info *info)
{
  char ch;
  int total;

  ch = (!info->has_minus && info->has_zero) ? '0' : ' ';
  total = info->arg_len;
  if (info->precision >= 0 && info->core == f_s && info->precision < info->arg_len)
    total = info->precision;
  if (info->is_negative || (info->has_plus && is_signed_core_flag(info->core)))
    total++;
  if (info->core == f_p ||
      (info->has_pound && (info->core == f_x || info->core == f_X)))
    total += 2;
  else if (info->core == f_o && info->has_pound)
    total++;
  if (info->is_negative && ch == '0')
    print_to_buf(buf, "-", 1);
  if (info->width > total)
    fill_buf(buf, ch, info->width - total);
}

static void print_prefix_arg(struct rz_buffer *buf, struct arg_info *info)
{
  if (is_signed_core_flag(info->core) && !info->has_zero)
    {
      if (info->is_negative)
	print_to_buf(buf, "-", 1);
      else if (info->has_plus)
	print_to_buf(buf, "+", 1);
    }
  if (info->core == f_p ||
      (info->has_pound && (info->core == f_x || info->core == f_X)))
    print_to_buf(buf, info->core != f_X ? "0x" : "0X", 2);
  else if (info->has_pound && info->core == f_o)
    print_to_buf(buf, "0", 1);
}

static void print_core_arg(struct rz_buffer *buf, struct arg_info *info, const char *arg)
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
	fill_buf(buf, '0', info->precision - info->arg_len);
    }
  print_to_buf(buf, arg, total);
}

static void print_arg(struct rz_buffer *buf, struct arg_info *info, const char *arg)
{
  if (*arg == '\0')
    return;
  info->arg_len = ft_strlen(arg);
  if (info->is_negative)
    info->arg_len--;
  if (!info->has_minus)
    print_pad(buf, info);
  print_prefix_arg(buf, info);
  print_core_arg(buf, info, arg);
  if (info->has_minus)
    print_pad(buf, info);
}

static void print_long_arg(struct rz_buffer *buf, struct arg_info *info, long arg)
{
  char str[21];
  
  if (info->size == f_hh)
    rz_ltoa(str, (signed char)arg);
  else if (info->size == f_h)
    rz_ltoa(str, (short)arg);
  else
    rz_ltoa(str, arg);
  info->is_negative = arg < 0;
  print_arg(buf, info, str);
}

static void print_double_arg(struct rz_buffer *buf, struct arg_info *info, double arg)
{
  char str[42];

  if (info->precision < 0)
    info->precision = 6;
  rz_ftoa(str, info, arg);
  info->is_negative = arg < 0;
  info->precision = -1;
  print_arg(buf, info, str);
}

static void print_char(struct rz_buffer *buf, struct arg_info *info, char ch)
{
  char str[2];

  str[0] = ch;
  str[1] = '\0';
  info->is_negative = 0;
  print_arg(buf, info, str);
}

static void print_ulong_arg(struct rz_buffer *buf, struct arg_info *info, unsigned long arg)
{
  char str[21];

  info->is_negative = 0;
  if (info->core == f_c)
    print_char(buf, info, arg);
  else if (info->core == f_s)
    print_arg(buf, info, (const char *)arg);
  else
    {
      if (info->size == f_hh)
	rz_ultoa(str, (unsigned char)arg, info->core);
      else if (info->size == f_h)
	rz_ultoa(str, (unsigned short)arg, info->core);
      else
	rz_ultoa(str, arg, info->core);
      print_arg(buf, info, str);
    }
}

static void print_fmt(struct rz_buffer *buf, struct arg_info *info, const char **s)
{
  const char *p;

  p = *s;
  if (info->va_conv == va_percent)
    print_to_buf(buf, "%", 1);
  else
    {
      while (*p && *p != '%')
	p++;
      print_to_buf(buf, *s, p - *s);
    }
  *s = p;
}

static void ft_printf_impl(struct rz_buffer *buf, const char *f, va_list ap)
{
  struct arg_info info;

  ft_memset(&info, '\0', sizeof(info));
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
	print_double_arg(buf, &info, va_arg(ap, double));
    }
}

int ft_printf(const char *f, ...)
{
  struct rz_buffer buf;
  va_list ap;

  if (!f)
    return (-1);
  buf.pos = buf.total = 0;
  va_start(ap, f);
  ft_printf_impl(&buf, f, ap);
  flush_buf(&buf);
  va_end(ap);
  return (buf.total);
}
