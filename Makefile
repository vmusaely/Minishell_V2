# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmusaely <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 15:53:07 by vmusaely          #+#    #+#              #
#    Updated: 2022/04/15 15:53:10 by vmusaely         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRCS = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJS = $(SRCS:src/%.c=obj/%.o)
CFLAGS = -Wall -Wextra -Werror -g -O0 -I./src 
LDFLAGS = $(CFLAGS) -lreadline
CFLAGS += -I ./readline/include
LDFLAGS += -L ./readline/lib -I ./readline/include

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -rf ./obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean re fclean all
