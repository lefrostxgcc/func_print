CC = gcc
CFLAGS = -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../ft_printf.h rz_write.h
SRCS := test_ft_printf.c rz_write.c
LDADD := `pkg-config --libs check`

OBJS = $(SRCS:.c=.o)

TARGET = test_ft_printf
LIBFTPRINTF = ../libftprintf.a

.PHONY: all clean fclean re force

all: $(TARGET)

vpath ..

$(TARGET): $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFTPRINTF): force
	$(MAKE) -C ..

force:

$(OBJS) : $(HEADERS)

clean:
	-rm -rf $(OBJS)

fclean: clean
	-rm -f $(TARGET)

re: fclean all
