NAME := libft.a
DNAME := libft_debug.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
DFLAGS := -g3 -fsanitize=address

SRCS := 
SRCS += ft_atoi.c
SRCS += ft_bzero.c
SRCS += ft_calloc.c
SRCS += ft_isalnum.c
SRCS += ft_isalpha.c
SRCS += ft_isascii.c
SRCS += ft_isdigit.c
SRCS += ft_isprint.c
SRCS += ft_itoa.c
SRCS += ft_memchr.c
SRCS += ft_memcmp.c
SRCS += ft_memcpy.c
SRCS += ft_memmove.c
SRCS += ft_memset.c
SRCS += ft_putchar_fd.c
SRCS += ft_putendl_fd.c
SRCS += ft_putnbr_fd.c
SRCS += ft_putstr_fd.c
SRCS += ft_split.c
SRCS += ft_strchr.c
SRCS += ft_strdup.c
SRCS += ft_striteri.c
SRCS += ft_strjoin.c
SRCS += ft_strlcat.c
SRCS += ft_strlcpy.c
SRCS += ft_strlen.c
SRCS += ft_strmapi.c
SRCS += ft_strncmp.c
SRCS += ft_strnstr.c
SRCS += ft_strrchr.c
SRCS += ft_strtrim.c
SRCS += ft_substr.c
SRCS += ft_tolower.c
SRCS += ft_toupper.c

OBJS := $(SRCS:.c=.o)
DOBJS := $(SRCS:.c=_d.o)
DEP := $(OBJS:.o=.d)
DDEP := $(DOBJS:.o=.d)

HEADER := $(shell find . -name '*.h')

.PHONY: all 
all: $(NAME)

.PHONY: debug
debug: $(DNAME)

$(NAME): $(OBJS)
	ar rc $@ $(OBJS)

$(DNAME): $(DOBJS)
	ar rc $@ $(DOBJS)

-include $(DEP)
%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@ 

-include $(DDEP)
%_d.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

.PHONY: clean 
clean:
	rm -f $(OBJS) $(DOBJS) $(DEP) $(DDEP)

.PHONY: fclean 
fclean: clean
	rm -f $(NAME) $(DNAME)

.PHONY: re
re: fclean all

.PHONY: fmt
fmt:
	clang-format -i --style=file $(SRCS) $(HEADER)
