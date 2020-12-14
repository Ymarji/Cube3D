/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarji <ymarji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 09:17:15 by ymarji            #+#    #+#             */
/*   Updated: 2020/12/04 12:57:33 by ymarji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)haystack;
	j = 0;
	i = 0;
	if (ft_strlen(needle) == 0)
		return (str);
	while (str[i])
	{
		if (str[i] == needle[0])
		{
			j = 1;
			while (str[i + j] == needle[j] && needle[j])
				j++;
			if (needle[j] == '\0')
				return (str + i);
		}
		i++;
	}
	return (0);
}
