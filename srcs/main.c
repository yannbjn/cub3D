/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:44:51 by yabejani          #+#    #+#             */
/*   Updated: 2024/08/29 21:12:44 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	destroy_mlx(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}

int	on_destroy(t_cub *cub)
{
	ft_free_all(cub);
	printf("Exit\n");
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		on_destroy(cub);
	if (keysym == XK_w)
		cub->vec->move[Y] = 1;
	if (keysym == XK_s)
		cub->vec->move[Y] = -1;
	if (keysym == XK_a)
		cub->vec->move[X] = -1;
	if (keysym == XK_d)
		cub->vec->move[X] = 1;
	if (keysym == XK_Left)
		cub->vec->rotate -= 1;
	if (keysym == XK_Right)
		cub->vec->rotate += 1;
	return (0);
}

int	handle_keyrelease(int key, t_cub *cub)
{
	if (key == XK_w && cub->vec->move[Y] == 1)
		cub->vec->move[Y] = 0;
	if (key == XK_s && cub->vec->move[Y] == -1)
		cub->vec->move[Y] = 0;
	if (key == XK_a && cub->vec->move[X] == -1)
		cub->vec->move[X] = 0;
	if (key == XK_d && cub->vec->move[X] == 1)
		cub->vec->move[X] = 0;
	if (key == XK_Left && cub->vec->rotate <= 1)
		cub->vec->rotate = 0;
	if (key == XK_Right && cub->vec->rotate >= 1)
		cub->vec->rotate = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	ft_init_struct(&cub);
	if (argc != 2)
		ft_error(&cub, "The only arg given must be a .cub file");
	parser(&cub, argv[1]);
	fill_spaces(&cub);
	check_walls(&cub);
	launch(&cub);
}
