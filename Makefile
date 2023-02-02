# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 15:04:49 by vlenard           #+#    #+#              #
#    Updated: 2023/02/02 16:01:48 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = 	src/main.c src/execute.c src/utils.c src/children.c \
		libft/get_next_line/get_next_line.c libft/get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(OBJS) $(LIBFT) -o $(NAME)
$(LIBFT): 
		cd libft && make && make clean
n:
		norminette $(SRC) $(NAME).h
clean :
		rm -f $(OBJS)
fclean : clean
		rm -f ./$(NAME)
re : fclean
		$(MAKE)
.PHONY: all, n, clean, fclean, re, v, $(LIBFT), $(NAME)