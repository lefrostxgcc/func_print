#include "rz_printf.h"
#include "libft/libft.h"
#include "tests/rz_write.h"

void rz_buf_flush(t_rz_buf *buf)
{
    buf->total += rz_write(0, buf->data, buf->pos);
    buf->pos = 0;
}

void rz_buf_fill(t_rz_buf *buf, char ch, int count)
{
    int free_count;

    while (count > 0)
    {
	free_count = (sizeof (buf->data)) - buf->pos;
	if (count > free_count)
	{
	    count -= free_count;
	    ft_memset(buf->data + buf->pos, ch, free_count);
	    rz_buf_flush(buf);
	}
	else
	{
	    ft_memset(buf->data + buf->pos, ch, count);
	    buf->pos += count;
	    count = 0;
	}
    }
}

void rz_buf_add(t_rz_buf *buf, const char *s, int s_len)
{
    int s_pos;
    int b_left;
    int s_left;

    s_pos = 0;
    while (s_pos < s_len)
    {
	b_left = (sizeof (buf->data)) - buf->pos;
	s_left = s_len - s_pos;
	if (s_left > b_left)
	{
	    s_left -= b_left;
	    ft_memcpy(buf->data + buf->pos, s + s_pos, b_left);
	    rz_buf_flush(buf);
	    s_pos += b_left;
	}
	else
	{
	    ft_memcpy(buf->data + buf->pos, s + s_pos, s_left);
	    buf->pos += s_left;
	    s_pos += s_left;
	}
    }
}
