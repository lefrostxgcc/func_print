AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS := ft_printf.h rz_printf.h tests/rz_write.h
FILES := ft_printf.c \
	rz_ltoa.c    \
        rz_ftoa.c    \
        rz_buf.c     \
        rz_parse.c   \
        rz_cast.c    \
	rz_utility.c \
        rz_print_type.c \
        rz_print_csu.c \
        rz_print_dif.c \
	rz_print_oxp.c \
	rz_ft.c

OBJS = $(FILES:.c=.o)

NAME = libftprintf.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $@ $^

$(OBJS) : $(FILES) $(HEADERS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
