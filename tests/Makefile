CC = gcc
CFLAGS = -DUNIT_TEST `pkg-config --cflags check`

HEADERS := ../ft_printf.h ../rz_numtostr.h rz_write.h
SRCS_PRINTF := test_ft_printf.c rz_write.c
SRCS_LTOA := test_rz_ltoa.c
SRCS_ULTOA := test_rz_ultoa.c
LDADD := `pkg-config --libs check`

OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)
OBJS_LTOA = $(SRCS_LTOA:.c=.o)
OBJS_ULTOA = $(SRCS_ULTOA:.c=.o)

TARGET_PRINTF := test_ft_printf
TARGET_LTOA := test_ltoa
TARGET_ULTOA := test_ultoa
LIBFTPRINTF := ../libftprintf.a

.PHONY: all clean fclean re force

all: $(TARGET_PRINTF) $(TARGET_LTOA) $(TARGET_ULTOA)

vpath ..

$(TARGET_PRINTF): $(OBJS_PRINTF) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(TARGET_LTOA): $(OBJS_LTOA) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(TARGET_ULTOA): $(OBJS_ULTOA) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(LDADD)

$(LIBFTPRINTF): force
	$(MAKE) -C ..

force:

$(OBJS) : $(HEADERS)

clean:
	-rm -rf $(OBJS_PRINTF) $(OBJS_LTOA) $(OBJS_ULTOA)

fclean: clean
	-rm -f $(TARGET_PRINTF) $(TARGET_LTOA) $(TARGET_ULTOA)
	$(MAKE) -C .. fclean

re: fclean all
