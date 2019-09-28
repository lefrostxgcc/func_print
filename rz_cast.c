#include "rz_printf.h"

static t_rz_cast_type rz_select_h_cast(const t_rz_arg_type type)
{
    if (type == type_d || type == type_i)
	return (cast_i);
    else
	return (cast_u);
}

static t_rz_cast_type rz_select_l_cast(const t_rz_arg *f)
{
    if (f->type == type_f)
    {
	if (f->size == size_L)
	    return (cast_long_double);
	else
	    return (cast_double);
    }
    else
    {
	if (f->type == type_d || f->type == type_i)
	    return (cast_l);
	else
	    return (cast_ul);
    }
}

t_rz_cast_type rz_select_cast(const t_rz_arg *f)
{
    if (f->size == size_hh || f->size == size_h)
	return (rz_select_h_cast(f->type));
    else if (f->size == size_l || f->size == size_ll || f->size == size_L)
	return (rz_select_l_cast(f));
    else if (f->type == type_f)
	return (cast_double);
    else if (f->type == type_d || f->type == type_i)
	return (cast_i);
    else if (f->type == type_u || f->type == type_o ||
	     f->type == type_x || f->type == type_X || f->type == type_c)
	return (cast_u);
    else if (f->type == type_s || f->type == type_p)
	return (cast_ul);
    else if (f->type == type_percent)
	return (cast_percent);
    return (cast_i);
}
