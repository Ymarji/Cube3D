/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:45:06 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/04 10:56:09 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	disttowall(t_cube *cube, double hordistence, double verdistence)
{
	cube->ray.washitvertical = 0;
	if (hordistence < verdistence)
	{
		cube->ray.distence = hordistence;
		cube->ray.xwallhit = cube->ray.xhit_h;
		cube->ray.ywallhit = cube->ray.yhit_h;
	}
	else
	{
		cube->ray.distence = verdistence;
		cube->ray.xwallhit = cube->ray.xhit_v;
		cube->ray.ywallhit = cube->ray.yhit_v;
		cube->ray.washitvertical = 1;
	}
}

void	spritevisible(t_cube *cube, int x, int y)
{
	int i;
	int dx;
	int dy;

	i = 0;
	while (i < cube->s_num)
	{
		dx = x / 64;
		dy = y / 64;
		if (dx == (int)(cube->sprite[i].pos.x / 64) &&
		dy == (int)(cube->sprite[i].pos.y / 64))
		{
			cube->sprite[i].visible = 1;
		}
		i++;
	}
}

void	ray_facing(t_cube *cube, double ray)
{
	cube->ray.facingdown = 0;
	cube->ray.facingup = 0;
	cube->ray.facingright = 0;
	cube->ray.facingleft = 0;
	if (ray > 0 && ray < M_PI)
		cube->ray.facingdown = 1;
	if (!cube->ray.facingdown)
		cube->ray.facingup = 1;
	if (ray < 0.5 * M_PI || ray > 1.5 * M_PI)
		cube->ray.facingright = 1;
	if (!cube->ray.facingright)
		cube->ray.facingleft = 1;
}

void	raycast(t_cube *cube, double rayangel)
{
	int horhit;
	int verhit;

	horhit = 0;
	verhit = 0;
	cube->ray.rayangel = normalizeangle(rayangel);
	ray_facing(cube, cube->ray.rayangel);
	horizentalcast(cube, &horhit);
	verticalcast(cube, &verhit);
	cube->ray.washitvertical = 0;
	calculdistancetowall(cube, horhit, verhit);
}

void	castingrays(t_cube *cube)
{
	int		w;
	double	rayangel;
	double	incstep;
	int		i;

	w = cube->file.widht;
	rayangel = normalizeangle(cube->ply.ro_angle - M_PI / 6.);
	incstep = M_PI / 3. / (double)w;
	i = 0;
	findingsprite(cube);
	while (i < w)
	{
		rayangel = cube->ply.ro_angle + atan((i - (w / 2)) / cube->dto_pl);
		raycast(cube, rayangel);
		cube->ray.distw[i] = cube->ray.distence;
		renderprojectedwalls(cube, i);
		i++;
	}
	sprite(cube);
}
