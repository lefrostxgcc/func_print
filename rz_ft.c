#include "rz_printf.h"

int rz_isdigit(int c)
{
    if (c >= '0' && c <= '9')
	return (1);
    else
	return (0);
}

void *rz_memcpy(void *dst, const void *src, size_t n)
{
    char *first;
    char *copy;
    
    first = (char *)src;
    copy = (char *)dst;
    while ((int)--n >= 0)
	*copy++ = *first++;
    return (dst);
}

char *rz_strcpy(char *dst, const char *src)
{
    int	i;
    
    i = 0;
    while (src[i] != '\0')
    {
	dst[i] = src[i];
	i++;
    }
    dst[i] = '\0';
    return (dst);
}

void *rz_memset(void *b, int c, size_t len)
{
    size_t			i;
    char			*a;
    unsigned char	q;
    
    i = 0;
    q = (unsigned char)c;
    a = (char *)b;
    if (len == 0)
	return (b);
    while (i < len)
    {
	a[i] = q;
	i++;
    }
    return (b);
}

size_t rz_strlen(const char *s)
{
    int	len;
    
    len = 0;
    if (!s)
	return (0);
    while (*s != '\0')
    {
	s++;
	len++;
    }
    return (len);
}
