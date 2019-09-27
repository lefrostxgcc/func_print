#ifndef RZ_NUMTOSTR_H
# define RZ_NUMTOSTR_H

enum va_conv_type {va_none, va_percent, va_i, va_u, va_l, va_ul,
		   va_double, va_long_double};
enum flag_type {f_c, f_s, f_p, f_d, f_i, f_u, f_o, f_x, f_X, f_percent, f_f};

enum rz_arg_size {size_none, size_hh, size_h, size_l, size_ll, size_L};

enum {BUFSIZE = 1024};

struct rz_buf
{
  char data[BUFSIZE];
  int pos;
  int total;
};

struct arg_info
{
  enum va_conv_type va_conv;
  enum rz_arg_size size;
  enum flag_type core;
  int minus;
  int plus;
  int sharp;
  int zero;
  int space;
  int is_negative;
  int width;
  int precision;
  int fmt_len;
  int arg_len;
};

void rz_ltoa(char *res, long number);
void rz_ultoa(char *res, unsigned long number, enum flag_type flag);
void rz_ftoa(char *res, struct arg_info *info, long double arg);
void rz_buf_flush(struct rz_buf *buf);
void rz_buf_fill(struct rz_buf *buf, char ch, int count);
void rz_buf_add(struct rz_buf *buf, const char *s, int len);

#endif
