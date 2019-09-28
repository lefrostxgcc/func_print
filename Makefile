AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS := ft_printf.h libft/libft.h rz_printf.h tests/rz_write.h
FILES := ft_printf.c rz_ltoa.c rz_ftoa.c rz_buf.c rz_parse.c rz_cast.c \
	rz_utility.c rz_print_arg.c rz_print_type.c

OBJS = $(FILES:.c=.o)

NAME = libftprintf.a

LIBFT := libft/libft.a

.PHONY: all clean fclean re force

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(AR) rcsT $@ $^

$(OBJS) : $(FILES) $(HEADERS)

$(LIBFT): force
	$(MAKE) -C libft

clean:
	rm -rf $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
