/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:11:18 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/09 14:15:37 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_sprite_angel(t_cube *cube)
{
	double	spriteangle;
	double	x;
	double	y;
	int		i;

	i = 0;
	while (i < cube->s_num)
	{
		spriteangle = 0;
		x = cube->sprite[i].pos.x - cube->ply.x_player;
		y = cube->sprite[i].pos.y - cube->ply.y_player;
		spriteangle = atan2(y, x);
		if (spriteangle <= 0.)
			cube->sprite[i].angl =
				(M_PI * 2) + spriteangle;
		else
			cube->sprite[i].angl = spriteangle;
		cube->sprite[i].angl =
		normalizeangle(cube->sprite[i].angl);
		i++;
	}
}

void	sprite(t_cube *cube)
{
	sortsprtis(cube);
	get_sprite_angel(cube);
	drowsprite(cube);
}
