/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:47:11 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/04 10:55:31 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	horizentalcast(t_cube *cube, int *horhit)
{
	cube->ray.yintercept =
		floor(cube->ply.y_player / cube->cube_d) * cube->cube_d;
	if (cube->ray.facingdown)
		cube->ray.yintercept += cube->cube_d;
	cube->ray.xintercept = cube->ply.x_player +
	(cube->ray.yintercept - cube->ply.y_player) / tan(cube->ray.rayangel);
	cube->ray.ystep = cube->cube_d;
	if (cube->ray.facingup)
		cube->ray.ystep *= -1;
	cube->ray.xstep = cube->cube_d / tan(cube->ray.rayangel);
	if (cube->ray.facingleft && cube->ray.xstep > 0)
		cube->ray.xstep *= -1;
	if (cube->ray.facingright && cube->ray.xstep < 0)
		cube->ray.xstep *= -1;
	check_horhit(cube, horhit);
}

void	check_horhit(t_cube *cube, int *horhit)
{
	double nextx;
	double nexty;

	nextx = cube->ray.xintercept;
	nexty = cube->ray.yintercept;
	while (nextx >= 0 &&
	nextx < (cube->cube_d * cube->file.maplinemax) && nexty >= 0 &&
	nexty < (cube->cube_d * cube->file.maprow))
	{
		if (its_a_wall(cube, nextx, nexty - cube->ray.facingup) == '1')
		{
			*horhit = 1;
			cube->ray.xhit_h = nextx;
			cube->ray.yhit_h = nexty;
			break ;
		}
		else
		{
			if (its_a_wall(cube, nextx, nexty - cube->ray.facingup) == '2')
				spritevisible(cube, nextx, nexty - cube->ray.facingup);
			nextx += cube->ray.xstep;
			nexty += cube->ray.ystep;
		}
	}
}

void	verticalcast(t_cube *cube, int *verhit)
{
	cube->ray.xintercept =
	floor(cube->ply.x_player / cube->cube_d) * cube->cube_d;
	if (cube->ray.facingright)
		cube->ray.xintercept += cube->cube_d;
	cube->ray.yintercept = cube->ply.y_player +
	(cube->ray.xintercept - cube->ply.x_player) * tan(cube->ray.rayangel);
	cube->ray.xstep = cube->cube_d;
	if (cube->ray.facingleft)
		cube->ray.xstep *= -1;
	cube->ray.ystep = tan(cube->ray.rayangel) * cube->cube_d;
	if (cube->ray.facingup && cube->ray.ystep > 0)
		cube->ray.ystep *= -1;
	if (cube->ray.facingdown && cube->ray.ystep < 0)
		cube->ray.ystep *= -1;
	check_vethit(cube, verhit);
}

void	check_vethit(t_cube *cube, int *verhit)
{
	double nextx;
	double nexty;

	nextx = cube->ray.xintercept;
	nexty = cube->ray.yintercept;
	while (nextx >= 0 &&
	nextx < (cube->cube_d * cube->file.maplinemax) &&
	nexty >= 0 && nexty < (cube->cube_d * cube->file.maprow))
	{
		if (its_a_wall(cube, nextx - cube->ray.facingleft, nexty) == '1')
		{
			*verhit = 1;
			cube->ray.xhit_v = nextx;
			cube->ray.yhit_v = nexty;
			break ;
		}
		else
		{
			if (its_a_wall(cube, nextx - cube->ray.facingleft, nexty) == '2')
				spritevisible(cube, nextx - cube->ray.facingleft, nexty);
			nextx += cube->ray.xstep;
			nexty += cube->ray.ystep;
		}
	}
}

void	calculdistancetowall(t_cube *cube, int horhit, int verhit)
{
	double hordistence;
	double verdistence;

	if (horhit)
		hordistence = dist2point(cube->ply.x_player,
		cube->ply.y_player, cube->ray.xhit_h, cube->ray.yhit_h);
	else
		hordistence = __INT_MAX__;
	if (verhit)
		verdistence = dist2point(cube->ply.x_player,
		cube->ply.y_player, cube->ray.xhit_v, cube->ray.yhit_v);
	else
		verdistence = __INT_MAX__;
	disttowall(cube, hordistence, verdistence);
}
