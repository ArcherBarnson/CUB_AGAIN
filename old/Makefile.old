# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 15:22:39 by bgrulois          #+#    #+#              #
#    Updated: 2023/03/29 22:54:30 by bgrulois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

GNL	=	./gnl

LFT	=	./libft

SRCS	=	${LFT}/ft_strdup.c \
		${LFT}/ft_atoi.c \
		${GNL}/get_next_line_utils.c \
		${GNL}/get_next_line.c \
		srcs/memtools.c \
		srcs/init.c \
		srcs/floodfill_utils.c \
		srcs/floodfill.c \
		srcs/parsing_utils.c \
		srcs/parsing_identifiers.c \
		srcs/parsing_colors.c \
		srcs/parsing.c \
		srcs/load.c \
		srcs/init_player.c \
		srcs/motion_control.c \
		srcs/render2d.c \
		srcs/render_3d.c \
		srcs/raycasting.c \
		srcs/raycasting_utils.c \
		srcs/main.c
		#test/textures_test_main.c

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3

OBJS	=	${SRCS:%.c=%.o}

all: 		${NAME}

%.o:		%.c
		$(CC) $(CFLAGS) -I /usr/include -I mlx_linux -c $< -o $@

#%.o:		%.c
#		$(CC) $(CFLAGS) -c $< -o $@

${NAME}: 	$(OBJS)
		make -C mlx_linux
		${CC} ${CFLAGS} $(OBJS) -L mlx_linux -lmlx -L /usr/lib -I mlx_linux -lXext -lX11 -lm -lz -o $(NAME)

#${NAME}: 	$(OBJS)
#		${CC} ${CFLAGS} $(OBJS) -o $(NAME)

clean:
		make clean -C mlx_linux
		rm -rf ${OBJS}

#clean:
#		rm -rf ${OBJS}

fclean:		clean
		rm -rf ${NAME}

re:		fclean
		make

.PHONY:		all clean fclean re
