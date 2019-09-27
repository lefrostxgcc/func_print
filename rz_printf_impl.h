#ifndef RZ_PRINTF_IMPL_H
# define RZ_PRINTF_IMPL_H

enum rz_cast_type {cast_none, cast_percent, cast_i, cast_u, cast_l, cast_ul,
		   cast_double, cast_long_double};
enum rz_arg_type {type_c, type_s, type_p, type_d, type_i,
		  type_u, type_o, type_x, type_X, type_f,
		  type_percent};

enum rz_arg_size {size_none, size_hh, size_h, size_l, size_ll, size_L};

enum {BUFSIZE = 1024};

struct rz_buf
{
  char data[BUFSIZE];
  int pos;
  int total;
};

struct rz_arg
{
  enum rz_cast_type cast;
  enum rz_arg_size size;
  enum rz_arg_type type;
  int minus;
  int plus;
  int sharp;
  int zero;
  int space;
  int negative;
  int width;
  int precision;
  int slen;
};

void rz_ltoa(char *res, long number);
void rz_ultoa(char *res, unsigned long number, enum rz_arg_type flag);
void rz_ftoa(char *res, struct rz_arg *info, long double arg);
void rz_buf_flush(struct rz_buf *buf);
void rz_buf_fill(struct rz_buf *buf, char ch, int count);
void rz_buf_add(struct rz_buf *buf, const char *s, int len);

#endif
