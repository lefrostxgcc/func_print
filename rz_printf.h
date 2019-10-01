#ifndef RZ_PRINTF_H
# define RZ_PRINTF_H
#include <unistd.h>

enum e_rz_cast_type {cast_none, cast_percent, cast_i, cast_u, cast_l,
		     cast_ul, cast_double, cast_long_double};
enum e_rz_arg_type {type_none, type_c, type_s, type_p, type_d, type_i,
		    type_u, type_o, type_x, type_X, type_f,
		    type_percent};

enum e_rz_arg_size {size_none, size_hh, size_h, size_l, size_ll, size_L};

typedef enum e_rz_cast_type t_rz_cast_type;
typedef enum e_rz_arg_type t_rz_arg_type;
typedef enum e_rz_arg_size t_rz_arg_size;

struct s_rz_buf
{
    char data[1024];
    int pos;
    int total;
};

struct s_rz_arg
{
    t_rz_cast_type cast;
    t_rz_arg_size size;
    t_rz_arg_type type;
    int minus;
    int plus;
    int sharp;
    int zero;
    int space;
    int negative;
    int argzero;
    int width;
    int precision;
    int floatzero;
    int slen;
    int fmtlen;
};

typedef struct s_rz_buf t_rz_buf;
typedef struct s_rz_arg t_rz_arg;

int rz_ltoa(char *res, t_rz_arg *f, long number);
int rz_ultoa(char *res, unsigned long number, t_rz_arg_type flag);
int rz_ftoa(char *res, t_rz_arg *info, long double arg);
void rz_buf_flush(t_rz_buf *buf);
void rz_buf_fill(t_rz_buf *buf, char ch, int count);
void rz_buf_add(t_rz_buf *buf, const char *s, int len);
void rz_parse_fmt(t_rz_buf *buf, t_rz_arg *f, const char **fmt);
int rz_read_integer_number(const char **s);
t_rz_cast_type rz_select_cast(const t_rz_arg *f);
int rz_signed(t_rz_arg_type t);
int rz_unsigned(t_rz_arg_type t);
int rz_number(t_rz_arg_type t);
void rz_print_as_long(t_rz_buf *buf, t_rz_arg *f, long arg);
void rz_print_as_ldouble(t_rz_buf *buf, t_rz_arg *f, long double arg);
void rz_print_as_ulong(t_rz_buf *buf, t_rz_arg *f, unsigned long arg);
void rz_print_fmt(t_rz_buf *buf, t_rz_arg *f, const char **s);
long rz_tern_l(int expression, long a, long b);
void *rz_tern_p(int expression, void *a, void *b);
void rz_print_type(t_rz_buf *buf, t_rz_arg *f, const char *arg);
void rz_print_type_cs(t_rz_buf *buf, t_rz_arg *f, const char *s);
void rz_print_type_u(t_rz_buf *buf, t_rz_arg *f, const char *s);
void rz_print_type_o(t_rz_buf *buf, t_rz_arg *f, const char *s);
void rz_print_type_x(t_rz_buf *buf, t_rz_arg *f, const char *s);
void rz_print_type_p(t_rz_buf *buf, t_rz_arg *f, const char *s);
void rz_print_type_di(t_rz_buf *buf, t_rz_arg *f, const char *s);
void rz_print_type_f(t_rz_buf *buf, t_rz_arg *f, const char *s);
int rz_isdigit(int c);
void *rz_memcpy(void *dst, const void *src, size_t n);
char *rz_strcpy(char *dst, const char *src);
void *rz_memset(void *b, int c, size_t len);
size_t rz_strlen(const char *s);
unsigned long rz_pow(int base, int exp);

#endif
