/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturegestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 09:17:12 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/05 11:12:14 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	calcul_x_y_pix_in_textu(t_cube *cube, int *xtext, int side)
{
	double stepx;

	stepx = ((double)cube->txt[side].width / (double)cube->cube_d);
	if (cube->ray.washitvertical == 0)
	{
		*xtext = (int)cube->ray.xwallhit % cube->cube_d;
	}
	else if (cube->ray.washitvertical == 1)
	{
		*xtext = (int)cube->ray.ywallhit % cube->cube_d;
	}
	*xtext = (double)*xtext * stepx;
}

void	textureload(t_cube *cube)
{
	cube->txt[N].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
	cube->file.no_text, &cube->txt[N].width, &cube->txt[N].hight);
	cube->txt[S].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
	cube->file.so_text, &cube->txt[S].width, &cube->txt[S].hight);
	cube->txt[E].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
	cube->file.ea_text, &cube->txt[E].width, &cube->txt[E].hight);
	cube->txt[W].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
	cube->file.we_text, &cube->txt[W].width, &cube->txt[W].hight);
	cube->txt[SP].img = mlx_xpm_file_to_image(cube->data.mlx_ptr,
	cube->file.s_text, &cube->txt[SP].width, &cube->txt[SP].hight);
	cube->txt[SP].addr = (int *)mlx_get_data_addr(cube->txt[SP].img,
	&cube->txt[SP].bpp, &cube->txt[SP].l_len, &cube->txt[SP].endian);
}

void	textselect(t_cube *cube)
{
	if (cube->ray.washitvertical == 0 && cube->ray.facingup)
		cube->txt[WALL].addr = (int *)mlx_get_data_addr(cube->txt[S].img,
		&cube->txt[S].bpp, &cube->txt[S].l_len, &cube->txt[S].endian);
	if (cube->ray.washitvertical == 0 && cube->ray.facingdown)
		cube->txt[WALL].addr = (int *)mlx_get_data_addr(cube->txt[N].img,
		&cube->txt[N].bpp, &cube->txt[N].l_len, &cube->txt[N].endian);
	if (cube->ray.washitvertical == 1 && cube->ray.facingright)
		cube->txt[WALL].addr = (int *)mlx_get_data_addr(cube->txt[W].img,
		&cube->txt[W].bpp, &cube->txt[W].l_len, &cube->txt[W].endian);
	if (cube->ray.washitvertical == 1 && cube->ray.facingleft)
		cube->txt[WALL].addr = (int *)mlx_get_data_addr(cube->txt[E].img,
		&cube->txt[E].bpp, &cube->txt[E].l_len, &cube->txt[E].endian);
}

void	textident(t_cube *cube)
{
	if (cube->ray.washitvertical == 0 && cube->ray.facingup)
		cube->ident = S;
	if (cube->ray.washitvertical == 0 && cube->ray.facingdown)
		cube->ident = N;
	if (cube->ray.washitvertical == 1 && cube->ray.facingright)
		cube->ident = W;
	if (cube->ray.washitvertical == 1 && cube->ray.facingleft)
		cube->ident = E;
}
