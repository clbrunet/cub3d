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

typedef struct	s_vector
{
	int		x;
	int		y;
}				t_vector;

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

typedef struct	s_config
{
	t_vector	res;
	t_textures	textures;
	t_color		floor_color;
	t_color		ceilling_color;
}				t_config;

typedef struct	s_player
{
	int			fov;
	int			height;
	t_vector	pos;
	int			angle;
}				t_player;

typedef struct	s_map
{
	char		**grid;
	t_vector	max;
}				t_map;

typedef struct	s_vars
{
	void		*mlx;
	t_config	config;
	t_map		map;
	t_player	player;
}				t_vars;

#endif
