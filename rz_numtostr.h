#ifndef RZ_NUMTOSTR_H
# define RZ_NUMTOSTR_H

enum va_conv_type {va_none, va_percent, va_i, va_u, va_l, va_ul,
		   va_double, va_long_double};
enum flag_type {f_c, f_s, f_p, f_d, f_i, f_u, f_o, f_x, f_X, f_percent,
		f_f, f_hh, f_h, f_l, f_ll, f_L};

enum {BUFSIZE = 1024};

struct rz_buffer
{
  char data[BUFSIZE];
  int pos;
  int total;
};

struct arg_info
{
  enum va_conv_type va_conv;
  enum flag_type size;
  enum flag_type core;
  int has_minus;
  int has_plus;
  int has_pound;
  int has_zero;
  int has_space;
  int is_negative;
  int width;
  int precision;
  int fmt_len;
  int arg_len;
};

void rz_ltoa(char *res, long number);
void rz_ultoa(char *res, unsigned long number, enum flag_type flag);
void rz_ftoa(char *res, struct arg_info *info, long double arg);
int digit_count(unsigned long n, unsigned base);

#endif
