/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:24:02 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/08 12:21:50 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	findingsprite(t_cube *cube)
{
	int i;
	int j;
	int cp;

	i = 0;
	j = 0;
	cp = 0;
	while (i < cube->file.maprow)
	{
		j = 0;
		while (j < cube->file.maplinemax)
		{
			if (cube->file.tab[i][j] == '2')
			{
				cube->sprite[cp].pos.x = j * cube->cube_d + (64 / 2);
				cube->sprite[cp].pos.y = i * cube->cube_d + (64 / 2);
				cube->sprite[cp].dist = dist2point(cube->sprite[cp].pos.x,
				cube->sprite[cp].pos.y, cube->ply.x_player, cube->ply.y_player);
				cube->sprite[cp].visible = 0;
				cp++;
			}
			j++;
		}
		i++;
	}
}

void	calcule_util(t_cube *cube, int i, int *s_x)
{
	int		s_hight;

	cube->sprite[i].dist = cube->sprite[i].dist * cos(cube->sprite[i].angl
	- cube->ply.ro_angle) + cube->cube_d / 4;
	cube->s_hight = (cube->cube_d / cube->sprite[i].dist) * cube->dto_pl;
	s_hight = cube->s_hight;
	*s_x = (tan(cube->fov / 2) * cube->dto_pl) + (tan(cube->sprite[i].angl
	- cube->ply.ro_angle) * cube->dto_pl) - (s_hight / 2);
}

void	drowsprite(t_cube *cube)
{
	int i;
	int x;
	int y;
	int s_x;

	i = 0;
	while (i < cube->s_num)
	{
		if (cube->sprite[i].visible == 1 &&
		cos(cube->sprite[i].angl - cube->ply.ro_angle) > 0)
		{
			x = 0;
			y = 0;
			calcule_util(cube, i, &s_x);
			while (x < cube->s_hight && x + s_x < cube->file.widht)
			{
				if (x + s_x >= 0)
					draw_s(cube, x, s_x, i);
				x++;
			}
		}
		i++;
	}
}

void	sprite_hight(t_cube *cube, int *start, int *end, int *i)
{
	if (*end - *start >= cube->file.hight)
	{
		*i += -*start;
		*start = 0;
		*end = cube->file.hight;
	}
}

void	draw_s(t_cube *cube, int x, int s_x, int sp)
{
	int color;
	int y;
	int start;
	int end;
	int i;

	i = 0;
	y = 0;
	start = cube->file.hight / 2 - cube->s_hight / 2;
	end = cube->file.hight / 2 + cube->s_hight / 2;
	sprite_hight(cube, &start, &end, &i);
	while (start < end)
	{
		y = i * ((double)cube->txt[SP].hight / (double)cube->s_hight);
		color = cube->txt[SP].addr[y * cube->txt[SP].width +
		(int)(x * ((double)cube->txt[SP].hight / (double)cube->s_hight))];
		if (color > 0x000000)
			if (s_x + x >= 0 && s_x + x < cube->file.widht)
				if (cube->ray.distw[x + s_x] > cube->sprite[sp].dist)
					cube->data.addr[start * cube->file.widht + x + s_x] = color;
		i++;
		start++;
	}
}
