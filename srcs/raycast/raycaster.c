/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:48:26 by yabejani          #+#    #+#             */
/*   Updated: 2024/08/29 21:26:28 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void	ft_img_addr(t_cub *cub, int **buffer, int i)
{
	int		j;
	int		index;
	t_img	img;

	zero_img(&img);
	img.mlx_img = mlx_new_image(cub->mlx, SCREEN_W, SCREEN_H);
	img.addr = (int *)mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len,
			&img.endian);
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
		{
			index = i * (img.line_len / 4) + j;
			if (buffer[i][j] > 0)
				img.addr[index] = buffer[i][j];
			else if (i < SCREEN_H / 2)
				img.addr[index] = cub->ccolor;
			else
				img.addr[index] = cub->fcolor;
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, img.mlx_img, 0, 0);
	mlx_destroy_image(cub->mlx, img.mlx_img);
}

static void	ft_reset_bigloop(int **buffer)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (i < SCREEN_H)
		i++;
	while (++j <= i)
		free(buffer[j]);
	free(buffer);
}

static void	ft_bigloop(t_cub *cub, t_vec *vec, int x, int **buffer)
{
	while (++x < SCREEN_W)
	{
		ft_ray_pos(vec, x);
		ft_sidedist(vec);
		ft_dda(cub, vec);
		ft_startdraw(vec);
		ft_draw(cub, vec, x, buffer);
	}
	ft_img_addr(cub, buffer, -1);
	ft_reset_bigloop(buffer);
}

void	raycaster(t_cub *cub, int i)
{
	t_vec	*vec;
	int		bufindex;
	int		**buffer;

	bufindex = -1;
	buffer = ft_calloc(SCREEN_H + 1, sizeof(int *));
	if (!buffer)
		ft_error(cub, MERROR);
	while (++bufindex < SCREEN_H)
	{
		buffer[bufindex] = ft_calloc(SCREEN_W + 1, sizeof(int));
		if (!buffer[bufindex])
		{
			while (++i < bufindex)
				free(buffer[bufindex]);
			free(buffer);
			ft_error(cub, MERROR);
		}
	}
	vec = cub->vec;
	vec->hit = 0;
	ft_bigloop(cub, vec, -1, buffer);
}

// void	raycaster(t_cub *cub)
// {
// 	t_vec	*vec;
// 	int		bufindex;
// 	int		**buffer;
// 	int		i;

// 	i = -1;
// 	bufindex = -1;
// 	buffer = ft_calloc(SCREEN_H + 1, sizeof(int *));
// 	if (!buffer)
// 		ft_error(cub, MERROR);
// 	while (++bufindex < SCREEN_H)
// 	{
// 		buffer[bufindex] = ft_calloc(SCREEN_W + 1, sizeof(int));
// 		if (!buffer[bufindex])
// 		{
// 			while (++i < bufindex)
// 				free(buffer[bufindex]);
// 			free(buffer);
// 			ft_error(cub, MERROR);
// 		}
// 	}
// 	vec = cub->vec;
// 	vec->hit = 0;
// 	ft_bigloop(cub, vec, -1, buffer);
// }
