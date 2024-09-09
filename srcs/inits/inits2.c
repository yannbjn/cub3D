/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:11:20 by jfita             #+#    #+#             */
/*   Updated: 2024/08/29 21:22:32 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	zero_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->img_width = 0;
	img->img_height = 0;
}

int	*fill_tex(t_cub *cub, char *tex)
{
	t_img	tmp;
	int		*array;
	int		x;
	int		y;

	load_xpm(cub, &tmp, tex);
	array = ft_calloc(1, sizeof(int) * (IMG_SIZE * IMG_SIZE));
	if (!array)
		ft_error(cub, MERROR);
	y = -1;
	while (++y < IMG_SIZE)
	{
		x = -1;
		while (++x < IMG_SIZE)
			array[y * IMG_SIZE + x] = tmp.addr[y * IMG_SIZE + x];
	}
	mlx_destroy_image(cub->mlx, tmp.mlx_img);
	return (array);
}

void	init_tex(t_cub *cub)
{
	cub->tex = ft_calloc(5, sizeof(int *));
	if (!cub->tex)
		ft_error(cub, MERROR);
	cub->tex[NO] = fill_tex(cub, cub->no);
	cub->tex[SO] = fill_tex(cub, cub->so);
	cub->tex[WE] = fill_tex(cub, cub->we);
	cub->tex[EA] = fill_tex(cub, cub->ea);
}

void	load_xpm(t_cub *cub, t_img *img, char *tex)
{
	zero_img(img);
	img->mlx_img = mlx_xpm_file_to_image(cub->mlx, tex, &img->img_width,
			&img->img_height);
	if (!img->mlx_img)
		ft_error(cub, MERROR);
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
}

void	launch(t_cub *cub)
{
	init_mlx(cub);
	init_vec(cub);
	init_tex(cub);
	raycaster(cub, -1);
	mlx_hook(cub->win, KeyPress, KeyPressMask, &handle_keypress, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, cub);
	mlx_hook(cub->win, DestroyNotify, 0, &on_destroy, cub);
	mlx_loop_hook(cub->mlx, &displaymoves, cub);
	mlx_loop(cub->mlx);
}
