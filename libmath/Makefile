# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherriau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 14:28:14 by aherriau          #+#    #+#              #
#    Updated: 2018/04/16 15:49:05 by aherriau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = libmath.a

SRC = vector_3d.c vector_3d_2.c vector_3d_3.c

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME):
	$(CC) -c $(SRC) $(CFLAGS)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

