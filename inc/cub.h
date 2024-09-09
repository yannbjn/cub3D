/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabejani <yabejani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:42:36 by yabejani          #+#    #+#             */
/*   Updated: 2024/09/03 18:57:54 by yabejani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MERROR "Malloc Error\n"
# define MISSINGINFO "Missing info before the map content\n"
# define MWALLS "Map not surrounded by walls\n"
# define RHAA "RGB code must contain only digits and commas\n"
# define ERRCOL "Error Color, (F or C must be 3 nb, \
separated by commas in range of [0-255])\n"
# define SCREEN_W 1280
# define SCREEN_H 720
# define X 0
# define Y 1
# define IMG_SIZE 64
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define P_SPEED 0.03
# define R_SPEED 0.04

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_vec
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	camera[2];
	double	raydir[2];
	double	sidedist[2];
	double	dd[2];
	int		map[2];
	int		step[2];
	int		tex[2];
	int		move[2];
	int		rotate;
	int		moved;
	int		lineh;
	int		drawstart;
	int		drawend;
	bool	hit;
	int		side;
	double	perpwalldist;
	int		texnum;
	double	wallx;
	double	texstep;
	double	texpos;
	int		color;
	int		y;
}			t_vec;

typedef struct s_cub
{
	int		needs;
	char	**map;
	size_t	height;
	size_t	width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	int		check;
	int		fcolor;
	int		ccolor;
	char	*c;
	int		tabf[3];
	int		tabc[3];
	t_vec	*vec;
	void	*mlx;
	void	*win;
	t_img	*img;
	int		**tex;
}			t_cub;

void		ft_error(t_cub *cub, char *errmsg);
void		parser(t_cub *cub, char *mapfile);
void		ft_check_doublelines(t_cub *cub, char *line, char *line2, int flag);
void		get_map(t_cub *cub, int fd, char *line);
int			is_digit_or_comma(char *str);
int			translate_color(int *rgb);
int			check_store_numbers(t_cub *cub, char **tmp, char type);

void		ft_start_parse(t_cub *cub, int fd);
int			ft_is_info(char *line);
void		ft_get_info2(t_cub *cub, char *line, int fd);
int			ft_check_suffix(char const *mapfile, int fd);
void		ft_get_info(t_cub *cub, char *line, int fd);
char		*ftsjb(char *s1, char *s2);
void		get_dims(t_cub *cub);
void		fill_spaces(t_cub *cub);
int			isstartorground(char c);
void		check_walls(t_cub *cub);

int			moving(t_cub *cub, t_vec *vec);
int			can_move(t_cub *cub, t_vec *vec, double x, double y);
int			y_move(t_cub *cub, t_vec *vec, int upordown);
int			x_move(t_cub *cub, t_vec *vec, int leftorright);
int			r_rotate(t_vec *vec);
int			l_rotate(t_vec *vec);
int			displaymoves(t_cub *cub);

void		ft_free_all(t_cub *cub);
void		ft_free_infos(t_cub *cub);
void		ft_free_tex(t_cub *cub);
void		destroy_mlx(t_cub *cub);

void		init_mlx(t_cub *cub);
void		init_vec(t_cub *cub);
void		ft_init_struct(t_cub *cub);
void		zero_img(t_img *img);
int			*fill_tex(t_cub *cub, char *tex);
void		init_tex(t_cub *cub);
void		load_xpm(t_cub *cub, t_img *img, char *tex);
void		launch(t_cub *cub);

void		raycaster(t_cub *cub, int i);
void		ft_ray_pos(t_vec *vec, int x);
void		ft_sidedist(t_vec *vec);
void		ft_dda(t_cub *cub, t_vec *vec);
void		ft_startdraw(t_vec *vec);
void		ft_draw(t_cub *cub, t_vec *vec, int x, int **buffer);

int			handle_keypress(int keysym, t_cub *cub);
int			handle_keyrelease(int key, t_cub *cub);
int			on_destroy(t_cub *cub);
void		destroy_mlx(t_cub *cub);
char		*ft_strdupfree(char *s, char *cursed);

#endif