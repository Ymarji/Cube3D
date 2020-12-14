/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:37:01 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/10 11:54:55 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int		vrf_arg_dg(char *tab, char *set)
{
	int		i;
	int		j;
	int		drapo;

	j = 0;
	i = 0;
	if (!tab || !*tab || !set)
		return (0);
	while (tab[i])
	{
		drapo = 0;
		j = 0;
		while (set[j])
		{
			if (tab[i] == set[j])
				drapo = 1;
			j++;
		}
		if (drapo == 0)
			return (0);
		i++;
	}
	return (1);
}

void	check_col(char **tab)
{
	int		i;
	char	*str;

	i = 0;
	while (i < 3)
	{
		str = ft_strtrim(tab[i], " ");
		if (!vrf_arg_dg(str, "0123456789"))
		{
			free(str);
			table_free(tab);
			err_print(COLOR_ERR, "error        ");
		}
		i++;
		free(str);
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	free_thing(t_cube *cube)
{
	if (cube->file.no_text)
		free(cube->file.no_text);
	if (cube->file.no_text)
		free(cube->file.so_text);
	if (cube->file.no_text)
		free(cube->file.ea_text);
	if (cube->file.no_text)
		free(cube->file.we_text);
	if (cube->file.no_text)
		free(cube->file.s_text);
}

void	init_file(t_cube *cube)
{
	cube->file.no_text = NULL;
	cube->file.ea_text = NULL;
	cube->file.we_text = NULL;
	cube->file.so_text = NULL;
	cube->file.s_text = NULL;
}
