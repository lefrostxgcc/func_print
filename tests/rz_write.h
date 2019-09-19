#ifndef RZ_WRITE_H
#define RZ_WRITE_H

#include <unistd.h>

const char *get_write_buf(void);
int get_write_len(void);
void free_write_buf(void);
ssize_t rz_write(int fd, const void *buf, size_t count);

#endif /* RZ_WRITE_H */
