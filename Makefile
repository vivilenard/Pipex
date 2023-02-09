# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 15:04:49 by vlenard           #+#    #+#              #
#    Updated: 2023/02/09 10:54:40 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = 	src/main.c src/execute.c src/utils.c src/children.c
BONUS = bonus/main_bonus.c bonus/execute_bonus.c bonus/utils_bonus.c bonus/children_bonus.c \
		libft/get_next_line/get_next_line.c libft/get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
OBJBONUS = $(BONUS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(OBJS) $(LIBFT) -o $(NAME)
bonus: $(LIBFT) $(OBJBONUS)
		$(CC) $(OBJBONUS) $(LIBFT) -o $(NAME)_bonus
$(LIBFT): 
		cd libft && make
n:
		norminette
clean :
		rm -f $(OBJS) $(OBJBONUS)
fclean : clean
		rm -f ./$(NAME) ./$(NAME)_bonus out
re : fclean
		$(MAKE)
.PHONY: all, n, clean, fclean, re