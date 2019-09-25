#ifndef RZ_NUMTOSTR_H
# define RZ_NUMTOSTR_H

enum va_conv_type {va_none, va_percent, va_i, va_u, va_l, va_ul};
enum flag_type {f_c, f_s, f_p, f_d, f_i, f_u, f_o, f_x, f_X, f_percent,
		f_hh, f_h, f_l, f_ll};
struct arg_info
{
  char buf[1024];
  int pos;
  enum va_conv_type va_conv;
  enum flag_type size;
  enum flag_type core;
  int has_minus;
  int has_plus;
  int has_pound;
  int has_zero;
  int is_negative;
  int width;
  int precision;
  int fmt_len;
  int arg_len;
  int total_len;
};

void rz_ltoa(char *res, long number);
void rz_ultoa(char *res, unsigned long number, enum flag_type flag);

#endif
