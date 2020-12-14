/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:44:38 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/08 12:22:52 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		its_a_wall(t_cube *cube, int x, int y)
{
	int till;
	int mapx;
	int mapy;

	till = cube->cube_d;
	mapx = x / till;
	mapy = y / till;
	return (cube->file.tab[mapy][mapx]);
}

void	draw_strip(t_cube *cube, int x, int side, int wallstrihigh)
{
	int color;
	int i;
	int xtext;
	int ytext;
	int start;

	i = 0;
	start = (cube->file.hight / 2) - (wallstrihigh / 2);
	cube->end = (cube->file.hight / 2) + (wallstrihigh / 2);
	calcul_x_y_pix_in_textu(cube, &xtext, side);
	if ((cube->end - start) >= cube->file.hight)
	{
		i += -start;
		start = 0;
		cube->end = cube->file.hight;
	}
	while (start < cube->end)
	{
		ytext = i * cube->txt[side].hight / (double)wallstrihigh;
		color = cube->txt[WALL].addr[ytext * cube->txt[side].width + xtext];
		cube->data.addr[start * cube->file.widht + x] = color;
		i++;
		start++;
	}
}

void	renderprojectedwalls(t_cube *cube, int i)
{
	double	raydistance;
	double	wallhight;
	double	truedist;

	raydistance = cube->ray.distence;
	truedist = raydistance *
	cos(cube->ray.rayangel - cube->ply.ro_angle);
	cube->dto_pl = (cube->file.widht / 2) / tan(cube->fov / 2);
	wallhight = (double)(cube->cube_d / truedist) * cube->dto_pl;
	colorfc(cube, wallhight, i);
	textselect(cube);
	textident(cube);
	draw_strip(cube, i, cube->ident, round(wallhight));
}
