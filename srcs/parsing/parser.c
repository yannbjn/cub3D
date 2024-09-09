/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:56:57 by yabejani          #+#    #+#             */
/*   Updated: 2024/09/03 19:24:28 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	free_tab_custom(char **tab, int index)
{
	int	i;

	i = 0;
	while (tab[i] || i == index)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_check_colors(t_cub *cub, char *str, char type)
{
	char	**tmp;
	int		i;

	str = ft_strtrim(str, "\n");
	if (!str)
		return (0);
	tmp = ft_split(str, ',');
	if (!tmp)
		return (0);
	i = -1;
	while (tmp[++i])
	{
		tmp[i] = ft_strtrimfree(tmp[i], " ");
		if (!tmp[i])
			return (free(str), free_tab_custom(tmp, i), 0);
		if (!is_digit_or_comma(tmp[i]))
			return (free_tab(tmp), free(str), 0);
		if (ft_strlen(tmp[i]) > 3 && ft_strlen(tmp[i]) < 1)
			return (free_tab(tmp), 0);
	}
	if (i != 3)
		return (free(str), free_tab(tmp), 0);
	return (free(str), check_store_numbers(cub, tmp, type));
}

void	check_map_chars(t_cub *cub)
{
	int	i;
	int	j;
	int	startpos;

	i = -1;
	startpos = 0;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != 'N' && cub->map[i][j] != 'S'
				&& cub->map[i][j] != 'E' && cub->map[i][j] != 'W'
				&& cub->map[i][j] != '1' && cub->map[i][j] != '0'
				&& cub->map[i][j] != ' ')
				ft_error(cub, "Map must contain only 0,1,N,S,E,W characters\n");
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				startpos++;
		}
	}
	if (startpos != 1)
		ft_error(cub, "Map must have 1 and only 1 starting pos (N,S,E,W)");
}

void	ft_start_parse(t_cub *cub, int fd)
{
	char	*line;

	line = ft_gnl_stack(fd);
	while (line && ft_is_info(line))
	{
		ft_get_info(cub, line, fd);
		free(line);
		line = NULL;
		line = ft_gnl_stack(fd);
	}
	if (!ft_check_colors(cub, cub->f, 'F')
		|| !ft_check_colors(cub, cub->c, 'C'))
	{
		if (line)
			free(line);
		(close(fd), ft_error(cub, ERRCOL));
	}
	get_map(cub, fd, line);
	check_map_chars(cub);
	cub->no = ft_strtrimfree(cub->no, "\n");
	cub->so = ft_strtrimfree(cub->so, "\n");
	cub->ea = ft_strtrimfree(cub->ea, "\n");
	cub->we = ft_strtrimfree(cub->we, "\n");
}

void	parser(t_cub *cub, char *mapfile)
{
	int	fd;

	fd = open(mapfile, __O_DIRECTORY);
	if (fd > 0)
		(close(fd), ft_error(cub,
				"Map should be a file and not a directory\n"));
	fd = open(mapfile, O_RDONLY);
	if (fd < 0 || !ft_check_suffix(mapfile, fd))
		ft_error(cub, "Must provide a valid .cub file!\n");
	ft_start_parse(cub, fd);
	if (cub->check != 6)
		(close(fd), ft_error(cub, "Duplicate or missing map info/texture\n"));
}
