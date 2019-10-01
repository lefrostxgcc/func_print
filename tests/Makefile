CC = gcc
CFLAGS = -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../ft_printf.h rz_write.h
SRCS := test_ft_printf.c rz_write.c
LDADD := `pkg-config --libs check`

OBJS = $(SRCS:.c=.o)

NAME := test_ft_printf
LIBFTPRINTF := ../libftprintf.a

.PHONY: all clean fclean re force

all: $(NAME)

vpath ..

$(NAME): $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFTPRINTF): force
	$(MAKE) -C ..

force:

$(OBJS) : $(HEADERS)

clean:
	-rm -rf $(OBJS)
	$(MAKE) -C .. clean

fclean: clean
	-rm -f $(NAME)
	$(MAKE) -C .. fclean

re: fclean all
