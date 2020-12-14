/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:22:29 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:23:34 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>
#include <stdlib.h>

void	initialise(t_cube *cube)
{
	cube->fov = M_PI / 3;
	cube->cube_d = 64;
	cube->file.playerfound = 0;
	cube->ray.distw = (int *)malloc(sizeof(int) * cube->file.widht);
	numofsprite(cube);
	cube->sprite = malloc(sizeof(t_sprite) * (cube->s_num + 1));
	cube->txt = malloc(sizeof(t_txt) * 7);
	textureload(cube);
	findplayer(cube);
	playerfacing(cube);
	cube->dto_pl = (cube->file.widht / 2) / tan(cube->fov / 2);
	cube->ply.radius = 5;
	cube->ply.turn_d = 0;
	cube->ply.walk_d = 0;
	cube->ply.ri_le = 0;
	cube->ply.move_s = 3;
	cube->ply.ro_speed = 1.3 * (M_PI / 180);
}

void	colorfc(t_cube *cube, double wallhight, int i)
{
	int		j;
	int		color;
	double	start;
	int		end;

	start = (cube->file.hight / 2) - (wallhight / 2);
	end = (cube->file.hight / 2) + (wallhight / 2);
	j = 0;
	while (j < start)
	{
		color = cube->file.colorc;
		if (j * cube->file.widht + i > 0)
			cube->data.addr[j * cube->file.widht + i] = color;
		j++;
	}
	j = end;
	while (j < cube->file.hight)
	{
		color = cube->file.colorf;
		if (j * cube->file.widht + i > 0)
			cube->data.addr[j * cube->file.widht + i] = color;
		j++;
	}
}

int		update(t_cube *cube)
{
	if (cube->ply.walk_d || cube->ply.turn_d || cube->ply.ri_le)
		player_updat(cube);
	if (cube->handle == 0)
		mlx_put_image_to_window(cube->data.mlx_ptr,
		cube->data.mlx_win, cube->data.img, 0, 0);
	return (0);
}

void	draw(t_cube *cube)
{
	castingrays(cube);
	if (cube->handle == 1)
	{
		image_create(cube);
		exit(0);
	}
}

int		main(int ac, char **av)
{
	t_cube cube;

	err_handler(ac, av, &cube);
	cube.data.mlx_ptr = mlx_init();
	initialise(&cube);
	if (cube.handle == 0)
		cube.data.mlx_win = mlx_new_window(cube.data.mlx_ptr,
		cube.file.widht, cube.file.hight, "cube 3d");
	cube.data.img = mlx_new_image(cube.data.mlx_ptr,
	cube.file.widht, cube.file.hight);
	cube.data.addr = (int *)mlx_get_data_addr(cube.data.img,
	&cube.data.bpp, &cube.data.l_len, &cube.data.endian);
	draw(&cube);
	if (cube.handle == 0)
	{
		mlx_hook(cube.data.mlx_win, 2, (1L << 0), key_press, &cube);
		mlx_hook(cube.data.mlx_win, 3, (1L << 1), key_release, &cube);
		mlx_hook(cube.data.mlx_win, 17, (1L << 5), ft_close_win, &cube);
		mlx_loop_hook(cube.data.mlx_ptr, update, &cube);
		mlx_loop(cube.data.mlx_ptr);
	}
	return (0);
}
