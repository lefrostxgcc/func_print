#include "rz_printf.h"

void rz_print_as_p(t_rz_buf *buf, t_rz_arg *f, void *p)
{
    char str_rep[21];
    const char *s;
    unsigned long num;

    if (p == NULL)
    {
	s = "(nil)";
	f->argzero = 1;
	f->slen = sizeof("(nil)") - 1;
    }
    else
    {
	num = (unsigned long) p;
	if (f->size == size_hh)
	    f->slen = rz_ultoa(str_rep, f, (unsigned char) num);
	else if (f->size == size_h)
	    f->slen = rz_ultoa(str_rep, f, (unsigned short) num);
	else
	    f->slen = rz_ultoa(str_rep, f, num);
	s = str_rep;
    }
    rz_print_type(buf, f, s);
}

void rz_print_as_s(t_rz_buf *buf, t_rz_arg *f, const char *s)
{
    if (s == NULL)
    {
	s = "(null)";
	f->argzero = 1;
    }
    f->slen = rz_strlen(s);
    rz_print_type(buf, f, s);
}
