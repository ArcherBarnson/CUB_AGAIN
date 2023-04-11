# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leina <leina@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 15:22:39 by bgrulois          #+#    #+#              #
#    Updated: 2023/04/05 18:47:38 by leina            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

GNL	=	gnl

LFT=	libft

OBJ_DIR = obj

LFT_FILES = ${LFT}/ft_strdup.c \
		${LFT}/ft_atoi.c

GNL_FILES = ${GNL}/get_next_line_utils.c \
		${GNL}/get_next_line.c
SRCS_DIR = srcs
SRCS	= srcs/memtools.c \
		srcs/init.c \
		srcs/floodfill_utils.c \
		srcs/floodfill_sub.c \
		srcs/floodfill.c \
		srcs/parsing_utils_ints.c \
		srcs/parsing_utils_mallocs.c \
		srcs/parsing_identifiers.c \
		srcs/parsing_colors.c \
		srcs/parsing.c \
		srcs/load.c \
		srcs/init_player.c \
		srcs/motion_ctl_utils.c \
		srcs/motion_control.c \
		srcs/keyboard_ctl.c \
		srcs/rendering_tools.c \
		srcs/render2d.c \
		srcs/render_3d.c \
		srcs/raycasting.c \
		srcs/raycasting_utils.c \
		srcs/main.c

ALL_FILES = $(LFT_FILES) \
		$(GNL_FILES) \
		$(SRCS)

OBJ_LFT = $(addprefix $(OBJ_DIR)/,$(LFT))

OBJ_GNL = $(addprefix $(OBJ_DIR)/,$(GNL))

OBJ_SRCS = $(addprefix $(OBJ_DIR)/,$(SRCS_DIR))

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3 -I /usr/include -I mlx_linux

all: 		${NAME}

$(OBJ_DIR):		;
	@mkdir -p $@
	@mkdir -p $(OBJ_LFT)
	@mkdir -p $(OBJ_GNL)
	@mkdir -p $(OBJ_SRCS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I /usr/include -I mlx_linux -c $< -o $@

OBJS = $(addprefix $(OBJ_DIR)/, $(ALL_FILES:.c=.o))

${NAME}: $(OBJ_DIR)	$(OBJS)
		make -C mlx_linux
		${CC} ${CFLAGS} $(OBJS) -L mlx_linux -lmlx -L /usr/lib -I mlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
		make clean -C mlx_linux
		rm -rf ${OBJ_DIR}
		rm -rf ${OBJS}

fclean:		clean
		rm -rf ${NAME}

re:		fclean
		make

.PHONY:		all clean fclean re
