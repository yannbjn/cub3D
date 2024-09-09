/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:56:14 by jfita             #+#    #+#             */
/*   Updated: 2024/09/03 18:01:47 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void	init_plane(t_vec *vec, char c)
{
	if (c == 'S')
	{
		vec->plane[0] = -0.66;
		vec->plane[1] = 0;
	}
	if (c == 'N')
	{
		vec->plane[0] = 0.66;
		vec->plane[1] = 0;
	}
	if (c == 'E')
	{
		vec->plane[0] = 0;
		vec->plane[1] = 0.66;
	}
	if (c == 'W')
	{
		vec->plane[0] = 0;
		vec->plane[1] = -0.66;
	}
}

static void	init_spawn(int y, int x, char c, t_vec *vec)
{
	vec->pos[0] = (double)x + 0.5;
	vec->pos[1] = (double)y + 0.5;
	if (c == 'S')
	{
		vec->dir[0] = 0;
		vec->dir[1] = 1;
	}
	else if (c == 'N')
	{
		vec->dir[0] = 0;
		vec->dir[1] = -1;
	}
	else if (c == 'E')
	{
		vec->dir[0] = 1;
		vec->dir[1] = 0;
	}
	else if (c == 'W')
	{
		vec->dir[0] = -1;
		vec->dir[1] = 0;
	}
	init_plane(vec, c);
}

void	init_vec(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	cub->vec = ft_calloc(1, sizeof(t_vec));
	if (!cub->vec)
		ft_error(cub, MERROR);
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
				init_spawn(i, j, cub->map[i][j], cub->vec);
		}
	}
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		ft_error(cub, MERROR);
	cub->win = mlx_new_window(cub->mlx, SCREEN_W, SCREEN_H,
			"���č̵̛̛͓̯̟͇̩̯̬̯̹̮̒̿̄̕ù̷̡͉̙̮̯̙͕͍̭̗̳̬̍͛̏̄̇̚͝͠b̵̢̧̧̧̢̗̜̦͖̜͇̩̳̍͊̀̌̋̅͘͝͝ͅ3̸̛̺͙̹̘̞͙͉͔̹͓̦̲̊́D̴̲͓̗̺̺͕̬͓̤̦̯͇̤̓͝  \
			芓芓芓LعLعLع");
	if (!cub->win)
		ft_error(cub, MERROR);
}

void	ft_init_struct(t_cub *cub)
{
	cub->needs = 0;
	cub->map = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
	cub->f = NULL;
	cub->c = NULL;
	cub->height = 0;
	cub->width = 0;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->tex = NULL;
	cub->vec = NULL;
	cub->check = 0;
}
