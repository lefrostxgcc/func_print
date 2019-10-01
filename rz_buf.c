#include "rz_printf.h"
#include "tests/rz_write.h"

void rz_buf_flush(t_rz_buf *buf)
{
    int bytes;

    bytes = rz_write(1, buf->data, buf->pos);
    if (buf->total >= 0)
	buf->total += bytes;
    buf->pos = 0;
}

void rz_buf_fill(t_rz_buf *buf, char ch, int count)
{
    int free_count;

    while (count > 0)
    {
	free_count = (sizeof (buf->data)) - buf->pos;
	if (count >= free_count)
	{
	    count -= free_count;
	    rz_memset(buf->data + buf->pos, ch, free_count);
	    buf->pos += free_count;
	    rz_buf_flush(buf);
	}
	else
	{
	    rz_memset(buf->data + buf->pos, ch, count);
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
    s_left = s_len;
    while (s_left > 0)
    {
	b_left = (sizeof (buf->data)) - buf->pos;
	if (s_left >= b_left)
	{
	    rz_memcpy(buf->data + buf->pos, s + s_pos, b_left);
	    buf->pos += b_left;
	    rz_buf_flush(buf);
	    s_pos += b_left;
	    s_left -= b_left;
	}
	else
	{
	    rz_memcpy(buf->data + buf->pos, s + s_pos, s_left);
	    buf->pos += s_left;
	    s_pos += s_left;
	    s_left = 0;
	}
    }
}
