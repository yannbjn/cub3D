/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 20:58:15 by jfita             #+#    #+#             */
/*   Updated: 2024/08/29 21:26:38 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int	r_rotate(t_vec *vec)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = vec->dir[X];
	old_planex = vec->plane[X];
	vec->dir[X] = vec->dir[X] * cos(R_SPEED) - vec->dir[Y] * sin(R_SPEED);
	vec->dir[Y] = old_dirx * sin(R_SPEED) + vec->dir[Y] * cos(R_SPEED);
	vec->plane[X] = vec->plane[X] * cos(R_SPEED) - vec->plane[Y] * sin(R_SPEED);
	vec->plane[Y] = old_planex * sin(R_SPEED) + vec->plane[Y] * cos(R_SPEED);
	return (1);
}

int	l_rotate(t_vec *vec)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = vec->dir[X];
	old_planex = vec->plane[X];
	vec->dir[X] = vec->dir[X] * cos(-R_SPEED) - vec->dir[Y] * sin(-R_SPEED);
	vec->dir[Y] = old_dirx * sin(-R_SPEED) + vec->dir[Y] * cos(-R_SPEED);
	vec->plane[X] = vec->plane[X] * cos(-R_SPEED) - vec->plane[Y]
		* sin(-R_SPEED);
	vec->plane[Y] = old_planex * sin(-R_SPEED) + vec->plane[Y] * cos(-R_SPEED);
	return (1);
}

int	displaymoves(t_cub *cub)
{
	cub->vec->moved += moving(cub, cub->vec);
	if (cub->vec->moved == 0)
		return (1);
	raycaster(cub, -1);
	return (0);
}
