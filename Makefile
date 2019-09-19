AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS := ft_printf.h tests/rz_write.h
FILES := ft_printf.c tests/rz_write.c

OBJS = $(FILES:.c=.o)

TARGET = libftprintf.a

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

$(OBJS) : $(FILES) $(HEADERS)

clean:
	rm -rf $(FILES:.c=.o) 

fclean: clean
	rm -f $(TARGET)

re: fclean all
