/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:54:09 by jfita             #+#    #+#             */
/*   Updated: 2024/08/29 21:22:34 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	moving(t_cub *cub, t_vec *vec)
{
	int	move;

	move = 0;
	if (vec->move[Y] == 1)
		move += y_move(cub, vec, 0);
	if (vec->move[Y] == -1)
		move += y_move(cub, vec, 1);
	if (vec->move[X] == -1)
		move += x_move(cub, vec, 0);
	if (vec->move[X] == 1)
		move += x_move(cub, vec, 1);
	if (vec->rotate < 0)
		move += l_rotate(vec);
	if (vec->rotate > 0)
		move += r_rotate(vec);
	return (move);
}

int	can_move(t_cub *cub, t_vec *vec, double x, double y)
{
	if (x < 0.25 || x >= cub->width - 1.25)
		return (0);
	if (vec->pos[Y] < 0.25 || vec->pos[Y] >= cub->height - 0.25)
		return (0);
	if (vec->pos[X] < 0.25 || vec->pos[X] >= cub->width - 1.25)
		return (0);
	if (y < 0.25 || y >= cub->height - 0.25)
		return (0);
	if (cub->map[(int)(y)][(int)(x)] == '1')
		return (0);
	return (1);
}

int	y_move(t_cub *cub, t_vec *vec, int upordown)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (upordown == 0)
	{
		x_tmp = vec->pos[X] + vec->dir[X] * (P_SPEED * 1.7);
		y_tmp = vec->pos[Y] + vec->dir[Y] * (P_SPEED * 1.7);
	}
	else if (upordown == 1)
	{
		x_tmp = vec->pos[X] - vec->dir[X] * (P_SPEED * 1.7);
		y_tmp = vec->pos[Y] - vec->dir[Y] * (P_SPEED * 1.7);
	}
	if (!can_move(cub, vec, x_tmp, y_tmp))
		return (0);
	else
	{
		vec->pos[X] = x_tmp;
		vec->pos[Y] = y_tmp;
	}
	return (1);
}

int	x_move(t_cub *cub, t_vec *vec, int leftorright)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = 0;
	y_tmp = 0;
	if (leftorright == 0)
	{
		x_tmp = vec->pos[X] + vec->dir[Y] * P_SPEED;
		y_tmp = vec->pos[Y] - vec->dir[X] * P_SPEED;
	}
	else if (leftorright == 1)
	{
		x_tmp = vec->pos[X] - vec->dir[Y] * P_SPEED;
		y_tmp = vec->pos[Y] + vec->dir[X] * P_SPEED;
	}
	if (!can_move(cub, vec, x_tmp, y_tmp))
		return (0);
	else
	{
		vec->pos[X] = x_tmp;
		vec->pos[Y] = y_tmp;
	}
	return (1);
}
