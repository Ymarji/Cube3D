/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 10:35:05 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/05 10:35:06 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		maplignemax(int fd)
{
	int		max;
	int		lent;
	int		res;
	char	*linee;

	lent = 0;
	res = 1;
	max = 0;
	while (res != 0)
	{
		res = get_next_line(fd, &linee);
		if (mapsearsh(linee))
		{
			lent = ft_strlen(linee);
		}
		if (lent > max)
			max = lent;
		free(linee);
	}
	return (max);
}

char	*complet_line(t_cube *cube, char *line)
{
	int		i;
	int		linelent;
	char	*tmp;

	tmp = line;
	linelent = ft_strlen(line);
	i = 0;
	if (linelent < cube->file.maplinemax)
	{
		line = (char *)malloc(sizeof(char) * (cube->file.maplinemax + 1));
		while (i < cube->file.maplinemax)
		{
			if (i < (int)strlen(tmp))
				line[i] = tmp[i];
			else
			{
				line[i] = ' ';
			}
			i++;
		}
		line[i] = '\0';
		free(tmp);
	}
	return (line);
}

void	maperr(t_cube *cube)
{
	int		x;
	int		y;
	char	**tmp;

	x = 0;
	y = 0;
	while (cube->file.tab[x] != NULL)
	{
		y = 0;
		tmp = ft_split(cube->file.tab[x], ' ');
		while (tmp[y] != NULL)
		{
			if ((tmp[y][0] != '1' && tmp[y][0] != ' ') ||
			(tmp[y][ft_strlen(tmp[y]) - 1] != '1' &&
			tmp[y][ft_strlen(tmp[y]) - 1] != ' '))
			{
				err_print(MAP_ERR, "maperr");
			}
			y++;
		}
		x++;
		table_free(tmp);
	}
}

int		countrow(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	mapoutlign(t_cube *cube, char **tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < cube->file.maplinemax)
	{
		if ((tab[0][j] != '1' && tab[0][j] != ' ') ||
		(tab[cube->file.maprow - 1][j] != '1' &&
		tab[cube->file.maprow - 1][j] != ' '))
		{
			err_print(MAP_ERR, "maooutlign");
		}
		j++;
	}
}
