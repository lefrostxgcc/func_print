#include <stdlib.h>
#include <string.h>
#include "rz_write.h"

static char *write_buf;
static int write_len;

const char *get_write_buf(void)
{
  return write_buf;
}

int get_write_len(void)
{
  return write_len;
}

void free_write_buf(void)
{
  free(write_buf);
  write_buf = NULL;
  write_len = 0;
}

ssize_t rz_write(int fd, const void *buf, size_t count)
{
  (void) fd;
  char *new_buf = malloc(write_len + count + 1);
  memcpy(new_buf, write_buf, write_len);
  memcpy(new_buf + write_len, buf, count);
  write_len += count;
  new_buf[write_len] = '\0';
  free(write_buf);
  write_buf = new_buf;
  return count;
}
