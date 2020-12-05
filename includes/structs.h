/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 07:21:52 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/29 07:51:35 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_dvector
{
	double	x;
	double	y;
}				t_dvector;

typedef struct	s_ivector
{
	int		x;
	int		y;
}				t_ivector;

typedef struct	s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
}				t_textures;

typedef union	u_color
{
	int				full;
	unsigned char	bytes[4];
}				t_color;

typedef struct	s_colors
{
	t_color		floor;
	t_color		ceilling;
}				t_colors;

typedef struct	s_player
{
	double		x;
	double		y;
	double		angle;
	double		fov;
	int			height;
}				t_player;

typedef struct	s_map
{
	char		**grid;
	double		minimap_factor;
	t_ivector	max;
}				t_map;

typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct	s_keys
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
}				t_keys;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_img_data	img;
	t_ivector	res;
	t_textures	textures;
	t_colors	colors;
	t_map		map;
	t_player	player;
	double		project_dist;
	t_keys		keys_down;
}				t_vars;

#endif
