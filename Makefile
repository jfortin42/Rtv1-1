# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <ldedier@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/06/26 16:26:47 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rtv1

CC		= gcc -g3 -Wall -Wextra -Werror

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
LIBFT = $(LIBFTDIR)/libft.a

LIBMATDIR = libmat
LIBMAT_INCLUDEDIR = includes
LIBMAT = $(LIBMATDIR)/libmat.a

LIBSDL2DIR = ~/.brew/lib
LIBSDL2_INCLUDEDIR = ~/.brew/Cellar/sdl2/2.0.8/include/SDL2/

SRCS_NO_PREFIX = main.c\
				 ft_init.c\
				 ft_init_2.c\
				 ft_loop.c\
				 ft_process.c\
				 ft_render.c\
				 ft_utils.c\
				 ft_matrix.c\
				 ft_events.c\
				 ft_events_2.c\
				 ft_intersections.c\
				 ft_trace.c\
				 ft_normals.c\
				 ft_objects.c\
				 ft_parse.c\
				 ft_parse_pos_rot_col.c\
				 ft_tools.c\
				 ft_parse_specifics.c

INCLUDES_NO_PREFIX = rtv1.h

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

LIBSDL2 = ./$(LIBSDL2DIR)/$(LIBSDL2_LIBDIR)/libSDL2-2.0.0.dylib

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBMATDIR)/$(LIBMAT_INCLUDEDIR) \
	  -I $(LIBSDL2_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC)

LFLAGS = -L $(LIBFTDIR) -lft -L $(LIBMATDIR) -lmat

opti:
	@make -j all

all:
	@make -C $(LIBFTDIR) all
	@make -C $(LIBMATDIR) all
	@make $(BINDIR)/$(NAME)

debug:
	@make -j all DEBUG=1

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT) $(LIBMAT)
	$(CC) -o $@ $^ $(LFLAGS) -L $(LIBSDL2DIR) -lsdl2
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(LIBMATDIR)
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(LIBMATDIR)

re: fclean opti

.PHONY: all clean fclean re
