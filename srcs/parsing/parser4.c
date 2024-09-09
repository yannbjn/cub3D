/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:04:28 by jfita             #+#    #+#             */
/*   Updated: 2024/09/03 19:04:31 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

char	*ft_strdupfree(char *s, char *cursed)
{
	size_t	i;
	char	*str;

	if (cursed)
		free(cursed);
	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	get_dims(t_cub *cub)
{
	int	i;

	i = -1;
	while (cub->map[++i])
	{
		if (ft_strlen(cub->map[i]) > cub->width)
			cub->width = ft_strlen(cub->map[i]);
	}
	cub->height = i - 1;
}

void	fill_spaces(t_cub *cub)
{
	char	*spaces;
	int		i;
	int		j;
	size_t	diff;

	get_dims(cub);
	i = -1;
	while (cub->map[++i])
	{
		diff = cub->width - ft_strlen(cub->map[i]);
		j = -1;
		spaces = ft_calloc((diff) + 1, sizeof(char));
		if (!spaces)
			ft_error(cub, MERROR);
		while (diff > 0)
		{
			spaces[++j] = 32;
			diff--;
		}
		if (cub->width - ft_strlen(cub->map[i]) > 0)
			cub->map[i] = ft_strjoinfree(cub->map[i], spaces);
		if (!cub->map[i])
			(free(spaces), ft_error(cub, MERROR));
		free(spaces);
	}
}

int	isstartorground(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	check_walls(t_cub *cub)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (cub->map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (isstartorground(cub->map[y][x]))
			{
				if (y == 0 || x == 0 || y == cub->height || x + 1 == cub->width)
					ft_error(cub, "Maps must be surrounded by walls\n");
				else if (cub->map[y + 1][x] == 32 || cub->map[y - 1][x] == 32
					|| cub->map[y][x + 1] == 32 || cub->map[y][x - 1] == 32)
					ft_error(cub, "Maps must be surrounded by walls\n");
			}
		}
	}
}
