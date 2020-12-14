/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:59:04 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:54:36 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	mapcheck(t_cube *cube, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < cube->file.maplinemax)
	{
		i = 0;
		while (i < cube->file.maprow)
		{
			if (tab[i][j] == ' ')
			{
				if (i > 0)
					if (tab[i - 1][j] != '1' && tab[i - 1][j] != ' ')
						err_print(MAP_ERR, "Map");
				if (i < cube->file.maprow - 1)
					if (tab[i + 1][j] != '1' && tab[i + 1][j] != ' ')
						err_print(MAP_ERR, "Map");
			}
			i++;
		}
		j++;
	}
}

void	mapalllong(char **tab)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] != '1' && tab[i][j] != '2' &&
			tab[i][j] != '0' && tab[i][j] != ' ' && tab[i][j] != 'N' &&
			tab[i][j] != 'S' && tab[i][j] != 'W' && tab[i][j] != 'E')
			{
				err_print(MAP_ERR, "Map");
			}
			j++;
		}
		i++;
	}
}

void	map_extract(t_cube *cube, char *line, int fd)
{
	char	*str;
	char	*tmp;
	char	*nline;
	int		ret;

	ret = -1;
	if (cube->file.args != 8)
		err_print(NUM_ARG, "0");
	str = ft_strjoin(line, "@");
	while (ret != 0)
	{
		ret = get_next_line(fd, &nline);
		if (nline[0] == '\0')
			nline[0] = ' ';
		tmp = str;
		str = ft_strjoin(str, nline);
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, "@");
		free(tmp);
		free(nline);
	}
	cube->file.tab = ft_split(str, '@');
	free(str);
	cube->file.maprow = countrow(cube->file.tab);
}

void	line_checker(t_cube *cube, char *line, int fd)
{
	int		i;

	i = -1;
	if (ft_strstr(line, "R ") || ft_strstr(line, "NO ")
	|| ft_strstr(line, "SO ") || ft_strstr(line, "WE ")
	|| ft_strstr(line, "EA ") || ft_strstr(line, "F ") || ft_strstr(line, "S ")
	|| ft_strstr(line, "C ") || line[0] == '\0')
	{
		if (line[0] != '\0')
			cube->file.args++;
		data_collector(cube, line);
	}
	else if (mapsearsh(line))
	{
		map_extract(cube, line, fd);
		while (cube->file.tab[++i] != NULL)
			cube->file.tab[i] = complet_line(cube, cube->file.tab[i]);
		mapoutlign(cube, cube->file.tab);
		maperr(cube);
		mapcheck(cube, cube->file.tab);
		mapalllong(cube->file.tab);
	}
	else
		err_print(KEY_ERR, line);
}

void	read_file(t_cube *cube, char *file)
{
	int		fd;
	int		fd1;
	int		ret;
	char	*line;

	ret = 1;
	cube->file.args = 0;
	init_file(cube);
	fd = open(file, O_RDONLY);
	fd1 = open(file, O_RDONLY);
	cube->file.maplinemax = maplignemax(fd1);
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		line_checker(cube, line, fd);
		free(line);
	}
	if (!cube->file.so_text || !cube->file.s_text ||
	!cube->file.we_text || !cube->file.no_text || !cube->file.ea_text)
	{
		free_thing(cube);
		err_print(NUM_ARG, "missing argument??\n");
	}
}
