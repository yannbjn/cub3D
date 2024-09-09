/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:01:25 by jfita             #+#    #+#             */
/*   Updated: 2024/09/03 18:40:42 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	ft_check_doublelines(t_cub *cub, char *line, char *line2, int flag)
{
	int	i;

	i = -1;
	if (line[0] == '\n')
	{
		if (line)
			free(line);
		if (line2)
			free(line2);
		ft_error(cub, "Empty line in map\n");
	}
	while (line[++i])
	{
		if (line[i] == '\n' && line[i + 1] == '\n')
			flag = 1;
		if (line[i] != '\n' && line[i] != '\0' && flag == 1)
		{
			if (line)
				free(line);
			if (line2)
				free(line2);
			ft_error(cub, "Empty line in map\n");
		}
	}
}

void	get_map(t_cub *cub, int fd, char *line)
{
	char	*line2;

	line2 = ft_gnl_stack(fd);
	if (!line2)
		(close(fd), ft_error(cub, "Empty map\n"));
	while (line2)
	{
		line = ftsjb(line, line2);
		if (!line)
			(close(fd), free(line2), ft_error(cub, MERROR));
		line2 = ft_gnl_stack(fd);
	}
	close(fd);
	ft_check_doublelines(cub, line, line2, 0);
	cub->map = ft_split(line, '\n');
	if (line)
		free(line);
	if (line2)
		free(line2);
	if (!cub->map)
		ft_error(cub, MERROR);
}

int	is_digit_or_comma(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '\n' && str[i])
			return (0);
	return (1);
}

int	translate_color(int *rgb)
{
	int	color;

	color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	return (color);
}

int	check_store_numbers(t_cub *cub, char **tmp, char type)
{
	int	i;

	i = -1;
	while (tmp[++i])
		if (ft_atoi(tmp[i]) > 255)
			return (free_tab(tmp), ft_error(cub,
					"Range of each nb of rgb code is [0-255]\n"), 0);
	i = -1;
	if (type == 'F')
		while (++i < 3)
			cub->tabf[i] = ft_atoi(tmp[i]);
	else if (type == 'C')
		while (++i < 3)
			cub->tabc[i] = ft_atoi(tmp[i]);
	free_tab(tmp);
	cub->fcolor = translate_color(cub->tabf);
	cub->ccolor = translate_color(cub->tabc);
	return (1);
}
