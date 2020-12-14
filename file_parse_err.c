/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 10:30:00 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:10:02 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	err_handler(int ac, char **av, t_cube *cube)
{
	char	**splited;
	char	*ext;

	cube->handle = 0;
	if (ac == 1 || ac > 3)
		err_print(NO_ARG, "0");
	splited = ft_split(av[1], '.');
	ext = splited[c_split(av[1], '.') - 1];
	if (ft_strcmp(ext, "cub") != 0)
		err_print(EXT_ERR, "0");
	if (open(av[1], O_RDONLY) == -1)
		err_print(NOT_ARG, "0");
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--save") != 0)
			err_print(NO_ARG, "0");
		else
			cube->handle = 1;
	}
	table_free(splited);
	read_file(cube, av[1]);
}

void	err_(int err, char *ident)
{
	if (err == FILE_ERR)
	{
		ft_putstr_fd(ident, 2);
		ft_putstr_fd(" -> File Not Found\n", 2);
	}
	if (err == COLOR_ERR)
	{
		ft_putstr_fd(ident, 2);
		ft_putstr_fd(" -> color invalide\t", 2);
	}
	if (err == MAP_ERR)
	{
		ft_putstr_fd(ident, 2);
		ft_putstr_fd(" -> MAP invalide!\n", 2);
	}
}

void	err_print(int err, char *ident)
{
	ft_putstr_fd("Error\n", 2);
	if (err == RES_ERR)
	{
		ft_putstr_fd(" -> Resulution\t", 2);
		ft_putstr_fd(ident, 2);
	}
	if (err == NO_ARG)
		ft_putstr_fd(" -> No arg!!\n", 2);
	if (err == NOT_ARG)
		ft_putstr_fd(" -> ARG Not Found!!\n", 2);
	if (err == EXT_ERR)
		ft_putstr_fd(" -> file invalide! <<need to be .cub>>\n", 2);
	if (err == KEY_ERR)
	{
		ft_putstr_fd(ident, 2);
		ft_putstr_fd(" -> ARG invalide!\n", 2);
	}
	if (err == NUM_ARG)
		ft_putstr_fd(" -> Number of ARG invalid\n", 2);
	err_(err, ident);
	exit(err);
}

int		mapsearsh(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
		i++;
	}
	return (0);
}
