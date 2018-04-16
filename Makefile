# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherriau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 14:31:09 by aherriau          #+#    #+#              #
#    Updated: 2018/04/16 18:07:13 by aherriau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = rtv1

SRC = srcs/main.c

OBJ = $(SRC:.c=.o)

LIBMATH_DIR = libmath


all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBMATH_DIR)
	$(CC) -o $@ $^ -L $(LIBMATH_DIR) -lmath -F ~/Library/Frameworks -framework SDL2

%.o: %.c srcs/main.h
	$(CC) -o $@ -c $< $(CFLAGS) -F ~/Library/Frameworks

clean:
	$(MAKE) $@ -C $(LIBMATH_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) $@ -C $(LIBMATH_DIR)
	rm -f $(NAME)

re: fclean all
