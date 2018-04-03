# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/04/03 20:59:43 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = rtv1

CC      = gcc

PWD = \"$(shell pwd)\"

DEBUG ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -fsanitize=address
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
LIBSDL2_LIBDIR = build

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX = main.c

INCLUDES_NO_PREFIX = rtv1.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))

OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))

INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))
INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR) -I $(LIBMATDIR)/$(LIBMAT_INCLUDEDIR) \
	  -I $(LIBSDL2DIR)/$(LIBSDL2_INCLUDEDIR)
CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC)

all: $(BINDIR)/$(NAME)

debug:
	@make all DEBUG=0

$(BINDIR)/$(NAME): $(OBJECTS)
	@make -C $(LIBFTDIR)
	@make -C $(LIBMATDIR)
	@./$(LIBSDL2DIR)/configure
	@make -C $(LIBSDL2DIR)
	@$(CC) -o $@ $^ -framework OpenGL -framework Appkit -L $(LIBFTDIR) -lft -L $(LIBMATDIR) -lmat -L\
		$(LIBSDL2DIR)/$(LIBSDL2_LIBDIR) -lsdl2
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(LIBMATDIR)
	@rm -f $(OBJECTS)

fclean: clean
	@make fclean -C $(LIBFTDIR)
