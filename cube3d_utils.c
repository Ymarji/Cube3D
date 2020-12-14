/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:50:16 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/05 11:15:27 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	dist2point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	normalizeangle(double angle)
{
	double res;

	res = remainder(angle, 2 * M_PI);
	if (res < 0)
	{
		res = (2 * M_PI) + res;
	}
	return (res);
}

void	table_free(char **tab)
{
	int i;
	int count;

	count = countrow(tab);
	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	numofsprite(t_cube *cube)
{
	int i;
	int j;
	int scont;

	scont = 0;
	i = 0;
	while (i < cube->file.maprow)
	{
		j = 0;
		while (j < cube->file.maplinemax)
		{
			if (cube->file.tab[i][j] == '2')
			{
				scont++;
			}
			j++;
		}
		i++;
	}
	cube->s_num = scont;
}

void	sortsprtis(t_cube *cube)
{
	int		i;
	int		j;
	double	tmp;

	i = -1;
	while (++i < cube->s_num - 1)
	{
		j = i;
		if (cube->sprite[i].dist < cube->sprite[j + 1].dist)
		{
			tmp = cube->sprite[i].dist;
			cube->sprite[i].dist = cube->sprite[j + 1].dist;
			cube->sprite[j + 1].dist = tmp;
			tmp = cube->sprite[i].visible;
			cube->sprite[i].visible = cube->sprite[j + 1].visible;
			cube->sprite[j + 1].visible = tmp;
			tmp = cube->sprite[i].pos.x;
			cube->sprite[i].pos.x = cube->sprite[j + 1].pos.x;
			cube->sprite[j + 1].pos.x = tmp;
			tmp = cube->sprite[i].pos.y;
			cube->sprite[i].pos.y = cube->sprite[j + 1].pos.y;
			cube->sprite[j + 1].pos.y = tmp;
			i = -1;
		}
	}
}
