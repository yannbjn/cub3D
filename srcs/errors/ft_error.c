/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:27:52 by yabejani          #+#    #+#             */
/*   Updated: 2024/09/06 15:56:37 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	ft_free_tex(t_cub *cub)
{
	if (cub->tex)
	{
		if (cub->tex[NO])
			free(cub->tex[NO]);
		if (cub->tex[SO])
			free(cub->tex[SO]);
		if (cub->tex[EA])
			free(cub->tex[EA]);
		if (cub->tex[WE])
			free(cub->tex[WE]);
	}
	if (cub->tex)
		free(cub->tex);
	if (cub->vec)
		free(cub->vec);
}

void	ft_free_all(t_cub *cub)
{
	if (cub->map)
		free_tab(cub->map);
	ft_free_infos(cub);
	ft_free_tex(cub);
	destroy_mlx(cub);
}

void	ft_free_infos(t_cub *cub)
{
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->we)
		free(cub->we);
	if (cub->ea)
		free(cub->ea);
	if (cub->f)
		free(cub->f);
	if (cub->c)
		free(cub->c);
}

void	ft_error(t_cub *cub, char *errmsg)
{
	fd_printf(2, "Error\n");
	if (errmsg)
		fd_printf(2, "%s", errmsg);
	ft_free_all(cub);
	exit(1);
}
