# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 10:44:52 by ymarji            #+#    #+#              #
#    Updated: 2020/12/09 12:42:10 by ymarji           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC		= gcc
CFLAGS = -Wall -Wextra -Werror

SRC = cube3d_utils.c\
    cube_sprite.c\
	draw_wall.c\
	wallcheck.c\
	find_player.c\
	file_parse.c\
	file_parse_util.c\
	file_parse_data.c\
	file_parse_err.c\
	file_parse_map.c\
	ft_strstr.c\
	image_save.c\
	cub3d.c\
	player_move.c\
	raycasting.c\
	raycasting_utils.c\
	ft_split.c\
	ft_putstr_fd.c\
	sprite.c\
	ft_memcpy.c\
	ft_atoi.c\
	gnl/get_next_line.c\
	gnl/get_next_line_utils.c\
	ft_strtrim.c\
	texturegestion.c
OBJ = ${SRC:.c=.o}

all:$(LIBFT) $(NAME) 

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit  -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all