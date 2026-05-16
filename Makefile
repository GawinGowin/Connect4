NAME := connect4
DNAME := $(NAME)_debug

SRCS :=
SRCS += src/main.c
SRCS += src/args.c
SRCS += src/board.c
SRCS += src/display.c
SRCS += src/display_ncurses.c
SRCS += src/win_check.c
SRCS += src/input.c
SRCS += src/input_ncurses.c
SRCS += src/io.c
SRCS += src/game_loop.c
SRCS += src/ai/ai.c
SRCS += src/ai/ai_heuristic.c
SRCS += src/ai/ai_negamax.c
SRCS += src/ai/ai_evaluate.c
SRCS += 

CC := cc
INCLUDES := -Iinclude
CFLAGS := -Wall -Wextra -Werror -MMD -MP $(INCLUDES)
LFLAGS := -Llib/libft -lft -lncurses
DFLAGS := -g3 -fsanitize=address
DLFLAGS := -Llib/libft -lft_debug -lncurses

LIB := lib/libft/libft.a
DLIB := lib/libft/libft_debug.a

OBJS := $(SRCS:.c=.o)
DOBJS := $(SRCS:.c=_d.o)
DEP := $(OBJS:.o=.d)
DDEP := $(DOBJS:.o=.d)

.PHONY: all
all: $(NAME)

$(LIB): FORCE
	make -C lib/libft -j4

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -O3 $^ $(LFLAGS) -o $@

.PHONY: debug
debug: $(DNAME)

$(DLIB): FORCE
	make -C lib/libft -j4 debug

$(DNAME): $(DLIB) $(DOBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $^ $(DLFLAGS) -o $@

-include $(DEP)
%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

-include $(DDEP)
%_d.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(DOBJS) $(DEP) $(DDEP) $(COV_INFO)
	make -C lib/libft fclean

.PHONY: fclean
fclean: clean
	rm -f $(NAME) $(DNAME)

.PHONY: re
re: fclean all

FORCE:

HEADER := $(shell find lib src include -name '*.h')

.PHONY: fmt
fmt:
	clang-format -i --style=file $(SRCS) $(HEADER)
