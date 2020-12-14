/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 09:44:00 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:55:23 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_res(t_cube *cube, char *line)
{
	char	**splited;
	char	*tmp;

	splited = ft_split(line, ' ');
	if (countrow(splited) != 3 || !vrf_arg_dg(splited[1], "0123456789")
	|| !vrf_arg_dg(splited[2], "0123456789"))
		err_print(RES_ERR, splited[0]);
	tmp = splited[1];
	splited[1] = ft_substr(splited[1], 0, 6);
	cube->file.widht = ft_atoi(splited[1]);
	free(tmp);
	tmp = splited[2];
	splited[2] = ft_substr(splited[2], 0, 6);
	cube->file.hight = ft_atoi(splited[2]);
	free(tmp);
	if (cube->file.widht > 2590)
		cube->file.widht = 2590;
	if (cube->file.hight > 1440)
		cube->file.hight = 1440;
	if (cube->file.widht <= 0 || cube->file.hight <= 0)
	{
		table_free(splited);
		err_print(RES_ERR, "error");
	}
	table_free(splited);
}

void	get_wall_text(char *line, char **textname)
{
	char	*splited;
	int		cp;

	splited = ft_strtrim(line, " ");
	*textname = ft_strdup(splited);
	cp = (int)ft_strlen(*textname);
	if (open(*textname, O_RDONLY) == -1 || splited[cp - 1] != 'm' ||
	splited[cp - 2] != 'p' || splited[cp - 3] != 'x')
	{
		free(splited);
		err_print(FILE_ERR, *textname);
	}
	free(splited);
}

int		colorassamble(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int		get_color(char *line)
{
	char	**splited;
	t_color	color;
	char	*tmp;
	int		cp;

	cp = 0;
	tmp = ft_strtrim(line, " ");
	cp = calc_ocur(line, ',');
	splited = ft_split(tmp, ',');
	if (countrow(splited) != 3 || cp != 2)
	{
		free(tmp);
		table_free(splited);
		err_print(COLOR_ERR, "error");
	}
	check_col(splited);
	color.r = ft_atoi(splited[0]);
	color.g = ft_atoi(splited[1]);
	color.b = ft_atoi(splited[2]);
	free(tmp);
	table_free(splited);
	if ((color.r > 255 || color.r < 0) || (color.g > 255 || color.g < 0) ||
	(color.b > 255 || color.b < 0))
		err_print(COLOR_ERR, "error");
	return (colorassamble(color.r, color.g, color.b));
}

void	data_collector(t_cube *cube, char *line)
{
	if (line[0] == ' ')
		err_print(KEY_ERR, line);
	if (line[0] == 'R')
		get_res(cube, line);
	else if (line[0] == 'N' && line[1] == 'O')
		get_wall_text(line + 2, &cube->file.no_text);
	else if (line[0] == 'S' && line[1] == 'O')
		get_wall_text(line + 2, &cube->file.so_text);
	else if (line[0] == 'W' && line[1] == 'E')
		get_wall_text(line + 2, &cube->file.we_text);
	else if (line[0] == 'E' && line[1] == 'A')
		get_wall_text(line + 2, &cube->file.ea_text);
	else if (line[0] == 'S' && line[1] == ' ')
		get_wall_text(line + 1, &cube->file.s_text);
	else if (line[0] == 'F')
		cube->file.colorf = (int)get_color(line + 1);
	else if (line[0] == 'C')
		cube->file.colorc = (int)get_color(line + 1);
}
