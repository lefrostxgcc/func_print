AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS := ft_printf.h libft/libft.h rz_numtostr.h tests/rz_write.h
FILES := ft_printf.c rz_ltoa.c

OBJS = $(FILES:.c=.o)

TARGET = libftprintf.a

LIBFT := libft/libft.a

.PHONY: all clean fclean re force

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBFT)
	$(AR) rcsT $@ $^

$(OBJS) : $(FILES) $(HEADERS)

$(LIBFT): force
	$(MAKE) -C libft

clean:
	rm -rf $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(TARGET)
	$(MAKE) -C libft fclean

re: fclean all
