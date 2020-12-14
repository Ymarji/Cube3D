/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallcheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 10:37:55 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:56:14 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		wall_check(t_cube *cube, double newx, double newy)
{
	int x;
	int y;
	int dist;
	int ret;

	x = newx;
	y = newy;
	dist = cube->cube_d / 8;
	ret = 0;
	if (its_a_wall(cube, x - dist, y - dist) == '1' ||
		its_a_wall(cube, x - dist, y - dist) == '2')
		ret = 1;
	if (its_a_wall(cube, x + dist, y - dist) == '1' ||
		its_a_wall(cube, x + dist, y - dist) == '2')
		ret = 1;
	if (its_a_wall(cube, x - dist, y + dist) == '1' ||
		its_a_wall(cube, x - dist, y + dist) == '2')
		ret = 1;
	if (its_a_wall(cube, x + dist, y + dist) == '1' ||
		its_a_wall(cube, x + dist, y + dist) == '2')
		ret = 1;
	return (ret);
}

int		calc_ocur(char *str, char c)
{
	int		cp;

	cp = 0;
	while (*str)
	{
		if (*str == c)
			cp++;
		str++;
	}
	return (cp);
}
