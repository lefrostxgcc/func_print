#ifndef RZ_NUMTOSTR_H
# define RZ_NUMTOSTR_H

enum va_conv_type {va_none, va_percent, va_i, va_u, va_l, va_ul};
enum flag_type {f_c, f_s, f_p, f_d, f_i, f_u, f_o, f_x, f_X, f_percent,
		f_hh, f_h, f_l, f_ll};
struct arg_info
{
  enum va_conv_type va_conv;
  enum flag_type size;
  enum flag_type core;
  int width;
  int precision;
  int fmt_len;
  int total_len;
};

char *rz_ltoa(long number);
char *rz_ultoa(unsigned long number, enum flag_type flag);
char *rz_otoa(unsigned long number);
char *rz_xtoa(unsigned long number);
char *rz_Xtoa(unsigned long number);
char *rz_ptoa(unsigned long number);

#endif
