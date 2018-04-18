# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/04/17 00:28:07 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rtv1

CC		= gcc -g

PWD = \"$(shell pwd)\"

OK_COLOR = \x1b[32;01m
EOC = \033[0m

DEBUG ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -fsanitize=address
else
	CFLAGS += -Ofast
endif

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes

LIBFTDIR = libft
LIBFT_INCLUDEDIR = includes

LIBMATDIR = libmat
LIBMAT_INCLUDEDIR = includes

LIBSDL2DIR = SDL2-2.0.8
LIBSDL2_INCLUDEDIR = include
LIBSDL2_LIBDIR = build/.libs

SRCS_NO_PREFIX = main.c ft_init.c ft_loop.c ft_events.c

INCLUDES_NO_PREFIX = rtv1.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

LIBSDL2 = ./$(LIBSDL2DIR)/$(LIBSDL2_LIBDIR)/libSDL2-2.0.0.dylib

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBMATDIR)/$(LIBMAT_INCLUDEDIR) \
	  -I $(LIBSDL2DIR)/$(LIBSDL2_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC)

LFLAGS = -L $(LIBFTDIR) -lft -L $(LIBMATDIR) -lmat\
		 -L $(LIBSDL2DIR)/$(LIBSDL2_LIBDIR) -lsdl2

opti:
	@make -j all

all: $(BINDIR)/$(NAME)

debug:
	@make -j all DEBUG=1

$(LIBSDL2):
	@cd $(LIBSDL2DIR);./configure
	@echo "$(OK_COLOR)$(NAME) SDL2 configured with success !$(EOC)"
	@make -C $(LIBSDL2DIR)
	@echo "$(OK_COLOR)SDL2 linked with success !$(EOC)"

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBSDL2)
	@make -C $(LIBFTDIR)
	@make -C $(LIBMATDIR)
	$(CC) -o $@ $^ $(LFLAGS) -fsanitize=address
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"
	@install_name_tool -change /usr/local/lib/libSDL2-2.0.0.dylib $(LIBSDL2) $(NAME)
	@echo $(NAME) > .gitignore
	@echo $(OBJECTS) >> .gitignore

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(LIBMATDIR)
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(LIBMATDIR)
	@make clean -C $(LIBSDL2DIR)

re: fclean opti

.PHONY: all clean fclean re
