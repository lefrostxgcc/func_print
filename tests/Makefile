CC = gcc
CFLAGS = -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../ft_printf.h ../rz_numtostr.h rz_write.h
SRCS_PRINTF := test_ft_printf.c rz_write.c
LDADD := `pkg-config --libs check`

OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)

TARGET_PRINTF := test_ft_printf
LIBFTPRINTF := ../libftprintf.a

.PHONY: all clean fclean re force

all: $(TARGET_PRINTF)

vpath ..

$(TARGET_PRINTF): $(OBJS_PRINTF) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFTPRINTF): force
	$(MAKE) -C ..

force:

$(OBJS) : $(HEADERS)

clean:
	-rm -rf $(OBJS_PRINTF)

fclean: clean
	-rm -f $(TARGET_PRINTF)
	$(MAKE) -C .. fclean

re: fclean all
