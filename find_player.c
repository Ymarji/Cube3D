/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 10:38:43 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:55:51 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	findplayer(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cube->file.tab[i])
	{
		j = 0;
		while (cube->file.tab[i][j])
		{
			if (cube->file.tab[i][j] == 'N' || cube->file.tab[i][j] == 'E' ||
				cube->file.tab[i][j] == 'W' || cube->file.tab[i][j] == 'S')
			{
				if (cube->file.playerfound == 1)
					err_print(MAP_ERR, "0");
				cube->ply.x_player = j * cube->cube_d + (cube->cube_d / 2);
				cube->ply.y_player = i * cube->cube_d + (cube->cube_d / 2);
				cube->file.playerfound = 1;
			}
			j++;
		}
		i++;
	}
	if (cube->file.playerfound == 0)
		err_print(MAP_ERR, "0");
}

void	playerfacing(t_cube *cube)
{
	int x;
	int y;

	x = cube->ply.x_player / cube->cube_d;
	y = cube->ply.y_player / cube->cube_d;
	if (cube->file.tab[y][x] == 'N')
	{
		cube->ply.ro_angle = 270 * M_PI / 180;
		cube->file.tab[y][x] = '0';
	}
	if (cube->file.tab[y][x] == 'S')
	{
		cube->ply.ro_angle = 90 * M_PI / 180;
		cube->file.tab[y][x] = '0';
	}
	if (cube->file.tab[y][x] == 'E')
	{
		cube->ply.ro_angle = 0 * M_PI / 180;
		cube->file.tab[y][x] = '0';
	}
	if (cube->file.tab[y][x] == 'W')
	{
		cube->ply.ro_angle = 180 * M_PI / 180;
		cube->file.tab[y][x] = '0';
	}
}

int		ft_close_win(t_cube *cube)
{
	free(cube->ray.distw);
	free(cube->sprite);
	free(cube->txt);
	free_thing(cube);
	exit(0);
}
