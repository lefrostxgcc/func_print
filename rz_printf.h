#ifndef RZ_PRINTF_H
# define RZ_PRINTF_H

enum e_rz_cast_type {cast_none, cast_percent, cast_i, cast_u, cast_l,
		     cast_ul, cast_double, cast_long_double};
enum e_rz_arg_type {type_c, type_s, type_p, type_d, type_i,
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
    int width;
    int precision;
    int slen;
};

typedef struct s_rz_buf t_rz_buf;
typedef struct s_rz_arg t_rz_arg;

void rz_ltoa(char *res, long number);
void rz_ultoa(char *res, unsigned long number, t_rz_arg_type flag);
void rz_ftoa(char *res, t_rz_arg *info, long double arg);
void rz_buf_flush(t_rz_buf *buf);
void rz_buf_fill(t_rz_buf *buf, char ch, int count);
void rz_buf_add(t_rz_buf *buf, const char *s, int len);

#endif
