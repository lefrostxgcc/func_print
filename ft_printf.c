#include <stdarg.h>
#include "ft_printf.h"
#include "rz_numtostr.h"
#include "libft/libft.h"

static int is_signed_core_flag(enum flag_type f)
{
  return f == f_d || f == f_i || f == f_p;
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

static void flush_buf(struct arg_info *info)
{
  info->total_len += rz_write(0, info->buf, info->pos);
  info->pos = 0;
}

static void fill_buf(struct arg_info *info, char ch, int count)
{
  int b_left;

  while (count > 0)
    {
      b_left = (sizeof (info->buf)) - info->pos;
      if (count > b_left)
	{
	  count -= b_left;
	  ft_memset(info->buf + info->pos, ch, b_left);
	  flush_buf(info);
	}
      else
	{
	  ft_memset(info->buf + info->pos, ch, count);
	  info->pos += count;
	  count = 0;
	}
    }
}

static void print_to_buf(struct arg_info *info, const char *s, int s_len)
{
  int s_pos;
  int b_left;
  int s_left;

  s_pos = 0;
  while (s_pos < s_len)
    {
      b_left = (sizeof (info->buf)) - info->pos;
      s_left = s_len - s_pos;
      if (s_left > b_left)
	{
	  s_left -= b_left;
	  ft_memcpy(info->buf + info->pos, s + s_pos, b_left);
	  flush_buf(info);
	  s_pos += b_left;
	}
      else
	{
	  ft_memcpy(info->buf + info->pos, s + s_pos, s_left);
	  info->pos += s_left;
	  s_pos += s_left;
	}
    }
}

static void print_pad(struct arg_info *info)
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
      print_to_buf(info, "-", 1);
  if (info->width > total)
    fill_buf(info, ch, info->width - total);
}

static void print_prefix_arg(struct arg_info *info)
{
  if (is_signed_core_flag(info->core) && !info->has_zero)
    {
      if (info->is_negative)
	print_to_buf(info, "-", 1);
      else if (info->has_plus)
	print_to_buf(info, "+", 1);
    }
  if (info->core == f_p ||
      (info->has_pound && (info->core == f_x || info->core == f_X)))
    print_to_buf(info, info->core != f_X ? "0x" : "0X", 2);
  else if (info->has_pound && info->core == f_o)
    print_to_buf(info, "0", 1);
}

static void print_core_arg(struct arg_info *info, const char *arg)
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
	fill_buf(info, '0', info->precision - info->arg_len);
    }
  print_to_buf(info, arg, total);
}

static void print_arg(struct arg_info *info, const char *arg)
{
  if (*arg == '\0')
    return;
  info->arg_len = ft_strlen(arg);
  if (info->is_negative)
    info->arg_len--;
  if (!info->has_minus)
    print_pad(info);
  print_prefix_arg(info);
  print_core_arg(info, arg);
  if (info->has_minus)
    print_pad(info);
}

static void print_long_arg(struct arg_info *info, long arg)
{
  char buf[21];
  
  if (info->size == f_hh)
    rz_ltoa(buf, (signed char)arg);
  else if (info->size == f_h)
    rz_ltoa(buf, (short)arg);
  else
    rz_ltoa(buf, arg);
  info->is_negative = arg < 0;
  print_arg(info, buf);
}

static void print_char(struct arg_info *info, char ch)
{
  char buf[2];

  buf[0] = ch;
  buf[1] = '\0';
  info->is_negative = 0;
  print_arg(info, buf);
}

static void print_ulong_arg(struct arg_info *info, unsigned long arg)
{
  char buf[21];

  info->is_negative = 0;
  if (info->core == f_c)
    print_char(info, arg);
  else if (info->core == f_s)
    print_arg(info, (const char *)arg);
  else
    {
      if (info->size == f_hh)
	rz_ultoa(buf, (unsigned char)arg, info->core);
      else if (info->size == f_h)
	rz_ultoa(buf, (unsigned short)arg, info->core);
      else
	rz_ultoa(buf, arg, info->core);
      print_arg(info, buf);
    }
}

static void print_fmt(struct arg_info *info, const char **s)
{
  const char *p;

  p = *s;
  if (info->va_conv == va_percent)
    print_to_buf(info, "%", 1);
  else
    {
      while (*p && *p != '%')
	p++;
      print_to_buf(info, *s, p - *s);
    }
  *s = p;
}

int ft_printf(const char *f, ...)
{
  struct arg_info info;
  va_list ap;

  if (!f)
    return -1;
  info.pos = info.total_len = 0;
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
  flush_buf(&info);
  va_end(ap);
  return info.total_len;
}
