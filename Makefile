NAME = minishell
CC = gcc
SRCS = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
CFLAGS = -Wall -Wextra -Werror -g -O0 -I./src 
LDFLAGS = $(CFLAGS) -lreadline

ifeq ($(shell uname -s), Darwin)
	CFLAGS += -I ~/.brew/opt/readline/include
	LDFLAGS += -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
endif

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
