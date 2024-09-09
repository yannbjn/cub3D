/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:49:54 by yabejani          #+#    #+#             */
/*   Updated: 2024/08/29 21:23:25 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	ft_ray_pos(t_vec *vec, int x)
{
	vec->camera[X] = 2 * x / (double)SCREEN_W - 1;
	vec->raydir[X] = vec->dir[X] + vec->plane[X] * vec->camera[X];
	vec->raydir[Y] = vec->dir[Y] + vec->plane[Y] * vec->camera[X];
	vec->map[X] = (int)vec->pos[X];
	vec->map[Y] = (int)vec->pos[Y];
	vec->dd[X] = fabs(1 / vec->raydir[X]);
	vec->dd[Y] = fabs(1 / vec->raydir[Y]);
}

void	ft_sidedist(t_vec *vec)
{
	if (vec->raydir[X] < 0)
	{
		vec->step[X] = -1;
		vec->sidedist[X] = ((vec->pos[X] - vec->map[X]) * vec->dd[X]);
	}
	else
	{
		vec->step[X] = 1;
		vec->sidedist[X] = ((vec->map[X] + 1.0 - vec->pos[X]) * vec->dd[X]);
	}
	if (vec->raydir[Y] < 0)
	{
		vec->step[Y] = -1;
		vec->sidedist[Y] = ((vec->pos[Y] - vec->map[Y]) * vec->dd[Y]);
	}
	else
	{
		vec->step[Y] = 1;
		vec->sidedist[Y] = ((vec->map[Y] + 1.0 - vec->pos[Y]) * vec->dd[Y]);
	}
}

void	ft_dda(t_cub *cub, t_vec *vec)
{
	vec->hit = 0;
	while (vec->hit == 0)
	{
		if (vec->sidedist[X] < vec->sidedist[Y])
		{
			vec->sidedist[X] += vec->dd[X];
			vec->map[X] += vec->step[X];
			vec->side = 0;
		}
		else
		{
			vec->sidedist[Y] += vec->dd[Y];
			vec->map[Y] += vec->step[Y];
			vec->side = 1;
		}
		if (vec->map[Y] < 0.25 || vec->map[X] < 0.25
			|| vec->map[Y] > cub->height - 0.25 || vec->map[X] > cub->width
			- 1.25)
			break ;
		if (cub->map[vec->map[Y]][vec->map[X]] == '1')
			vec->hit = 1;
	}
}

void	ft_startdraw(t_vec *vec)
{
	if (vec->side == 0)
		vec->perpwalldist = vec->sidedist[X] - vec->dd[X];
	else
		vec->perpwalldist = vec->sidedist[Y] - vec->dd[Y];
	vec->lineh = (int)(SCREEN_H / vec->perpwalldist);
	vec->drawstart = -(vec->lineh) / 2 + SCREEN_H / 2;
	if (vec->drawstart < 0)
		vec->drawstart = 0;
	vec->drawend = vec->lineh / 2 + SCREEN_H / 2;
	if (vec->drawend >= SCREEN_H)
		vec->drawend = SCREEN_H - 1;
	if (vec->side == 0)
	{
		if (vec->raydir[X] < 0)
			vec->texnum = WE;
		else
			vec->texnum = EA;
	}
	else
	{
		if (vec->raydir[Y] > 0)
			vec->texnum = SO;
		else
			vec->texnum = NO;
	}
}

void	ft_draw(t_cub *cub, t_vec *vec, int x, int **buffer)
{
	if (vec->side == 0)
		vec->wallx = vec->pos[Y] + vec->perpwalldist * vec->raydir[Y];
	else
		vec->wallx = vec->pos[X] + vec->perpwalldist * vec->raydir[X];
	vec->wallx -= floor(vec->wallx);
	vec->tex[X] = (int)(vec->wallx * (double)IMG_SIZE);
	if (vec->side == 0 && vec->raydir[X] > 0)
		vec->tex[X] = IMG_SIZE - vec->tex[X] - 1;
	if (vec->side == 1 && vec->raydir[Y] < 0)
		vec->tex[X] = IMG_SIZE - vec->tex[X] - 1;
	vec->texstep = 1.0 * IMG_SIZE / vec->lineh;
	vec->texpos = (vec->drawstart - SCREEN_H / 2 + vec->lineh / 2)
		* vec->texstep;
	vec->y = vec->drawstart - 1;
	while (++vec->y < vec->drawend)
	{
		vec->tex[Y] = (int)vec->texpos & (IMG_SIZE - 1);
		vec->texpos += vec->texstep;
		vec->color = cub->tex[vec->texnum][IMG_SIZE * vec->tex[Y]
			+ vec->tex[X]];
		buffer[vec->y][x] = vec->color;
	}
}
