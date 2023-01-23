# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 13:39:13 by vlenard           #+#    #+#              #
#    Updated: 2022/12/09 09:58:22 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = get_next_line.c get_next_line_utils.c
BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS = $(SRC:.c=.o)
OBJB = $(BONUS:.c=.o)
NAME = gnl.a
NAMEBONUS = gnlbonus.a
N = 1

all: $(NAME) 
$(NAME) : $(OBJS) 
		ar rcs $(NAME) $(OBJS)
$(NAMEBONUS) : $(OBJB) 
		ar rcs $(NAMEBONUS) $(OBJB)
c: all
		$(CC)  $(NAME) -D BUFFER_SIZE=$(N) main.c && ./a.out
bonus: $(NAMEBONUS)
		$(CC)  $(NAMEBONUS) -D BUFFER_SIZE=$(N) main.c && ./a.out
n:
		norminette $(SRC)
clean :
		rm -f $(OBJS) $(OBJB)
fclean : clean
		rm -f $(NAME) $(NAMEBONUS)
re : fclean
		$(MAKE) all
.PHONY: all, m, b, n, clean, fclean, re