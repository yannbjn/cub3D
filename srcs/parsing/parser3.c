/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:03:29 by jfita             #+#    #+#             */
/*   Updated: 2024/09/03 18:58:28 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	ft_check_suffix(const char *mapfile, int fd)
{
	size_t	n;

	n = ft_strlen(mapfile);
	if (n < 4 || mapfile[n - 1] != 'b' || mapfile[n - 2] != 'u'
		|| mapfile[n - 3] != 'c' || mapfile[n - 4] != '.')
		return (close(fd), 0);
	return (1);
}

void	ft_get_info2(t_cub *cub, char *line, int fd)
{
	while (*line == 32)
		line++;
	if (!ft_strncmp(line, "EA ", 3))
	{
		cub->check++;
		cub->ea = ft_strdupfree(line + 3, cub->ea);
		if (!cub->ea)
			(close(fd), ft_error(cub, MERROR));
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		cub->check++;
		cub->f = ft_strdupfree(line + 2, cub->f);
		if (!cub->f)
			(close(fd), ft_error(cub, MERROR));
	}
	if (!ft_strncmp(line, "C ", 2))
	{
		cub->check++;
		cub->c = ft_strdupfree(line + 2, cub->c);
		if (!cub->c)
			(close(fd), ft_error(cub, MERROR));
	}
}

void	ft_get_info(t_cub *cub, char *line, int fd)
{
	while (*line == 32)
		line++;
	if (!ft_strncmp(line, "NO ", 3))
	{
		cub->check++;
		cub->no = ft_strdupfree(line + 3, cub->no);
		if (!cub->no)
			(close(fd), ft_error(cub, MERROR));
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		cub->check++;
		cub->so = ft_strdupfree(line + 3, cub->so);
		if (!cub->so)
			(close(fd), ft_error(cub, MERROR));
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		cub->check++;
		cub->we = ft_strdupfree(line + 3, cub->we);
		if (!cub->we)
			(close(fd), ft_error(cub, MERROR));
	}
	ft_get_info2(cub, line, fd);
}

int	ft_is_info(char *line)
{
	while (*line == 32)
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	else if (!ft_strncmp(line, "SO ", 3))
		return (1);
	else if (!ft_strncmp(line, "WE ", 3))
		return (1);
	else if (!ft_strncmp(line, "EA ", 3))
		return (1);
	else if (!ft_strncmp(line, "F ", 2))
		return (1);
	else if (!ft_strncmp(line, "C ", 2))
		return (1);
	else if (line[0] == '\n')
		return (1);
	else
		return (0);
}

char	*ftsjb(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
