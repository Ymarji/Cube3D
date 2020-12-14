/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:42:57 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:50:22 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	player_updat(t_cube *cube)
{
	double move_s;
	double move_s1;
	double new_x;
	double new_y;

	new_x = cube->ply.x_player;
	new_y = cube->ply.y_player;
	cube->ply.ro_angle = normalizeangle(cube->ply.ro_angle);
	cube->ply.ro_angle += cube->ply.turn_d * cube->ply.ro_speed;
	move_s = cube->ply.walk_d * cube->ply.move_s;
	move_s1 = cube->ply.ri_le * cube->ply.move_s;
	new_x = cube->ply.x_player + cos(cube->ply.ro_angle) * move_s;
	new_y = cube->ply.y_player + sin(cube->ply.ro_angle) * move_s;
	new_x = new_x + cos(cube->ply.ro_angle - (90 * M_PI / 180)) * move_s1;
	new_y = new_y + sin(cube->ply.ro_angle - (90 * M_PI / 180)) * move_s1;
	ray_facing(cube, cube->ply.ro_angle);
	if (wall_check(cube, new_x, cube->ply.y_player) != 1)
		cube->ply.x_player = new_x;
	if (wall_check(cube, cube->ply.x_player, new_y) != 1)
		cube->ply.y_player = new_y;
	draw(cube);
}

int		key_press(int key, t_cube *cube)
{
	if (key == 53)
		ft_close_win(cube);
	if (key == W_KEY)
		cube->ply.walk_d = +1;
	if (key == S_KEY)
		cube->ply.walk_d = -1;
	if (key == RIGHT_KEY)
		cube->ply.turn_d = +1;
	if (key == LEFT_KEY)
		cube->ply.turn_d = -1;
	if (key == D_KEY)
		cube->ply.ri_le = -1;
	if (key == A_KEY)
		cube->ply.ri_le = +1;
	return (0);
}

int		key_release(int key, t_cube *cube)
{
	if (key == W_KEY)
		cube->ply.walk_d = 0;
	if (key == S_KEY)
		cube->ply.walk_d = 0;
	if (key == RIGHT_KEY)
		cube->ply.turn_d = 0;
	if (key == LEFT_KEY)
		cube->ply.turn_d = 0;
	if (key == D_KEY)
		cube->ply.ri_le = 0;
	if (key == A_KEY)
		cube->ply.ri_le = 0;
	return (0);
}
