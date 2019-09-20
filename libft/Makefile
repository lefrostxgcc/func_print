AR = ar
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS := libft.h
FILES := $(wildcard *.c)

OBJS = $(FILES:.c=.o)

TARGET = libft.a

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
