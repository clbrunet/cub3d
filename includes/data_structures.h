/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 07:21:52 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/12 18:45:43 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef enum	e_error
{
	PERROR,
	ERROR
}				t_error;

typedef enum	e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_orientation;

typedef struct	s_argb
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	alpha;
}				t_argb;

typedef union	u_color
{
	unsigned	full;
	t_argb		bytes;
}				t_color;

typedef struct	s_bgr
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
}				t_bgr;

typedef union	u_bmp_color
{
	unsigned char	str[3];
	t_bgr			bgr;
}				t_bmp_color;

typedef union	u_bmp_field
{
	unsigned		full;
	unsigned char	str[4];
}				t_bmp_field;

typedef struct	s_dvector
{
	double	x;
	double	y;
}				t_dvector;

typedef struct	s_uvector
{
	unsigned	x;
	unsigned	y;
}				t_uvector;

typedef struct	s_dline
{
	t_dvector	p1;
	t_dvector	p2;
}				t_dline;

typedef struct	s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct	s_texture
{
	t_img_data	img;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_textures
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	monster;
	t_texture	regeneration;
	t_texture	health;
	t_texture	floor;
	t_texture	ceilling;
	t_texture	weapon[6];
}				t_textures;

typedef struct	s_player
{
	t_dvector	pos;
	double		angle;
	double		fov;
	double		speed;
	unsigned	height;
	unsigned	health;
}				t_player;

typedef struct	s_map
{
	char		**grid;
	double		minimap_factor;
	t_uvector	max;
}				t_map;

typedef struct	s_keys
{
	char	left;
	char	right;
	char	z;
	char	q;
	char	s;
	char	d;
	char	lshift;
	char	up;
	char	down;
	char	lctrl;
	char	f;
}				t_keys;

typedef struct	s_hit
{
	t_dvector	pos;
	double		distance;
	unsigned	height;
	unsigned	offset;
	char		map_char;
}				t_hit;

typedef struct	s_ray
{
	unsigned		col;
	double			angle;
	t_orientation	orientation[2];
	t_hit			h_hit;
	char			h_yshift;
	t_dvector		h_step;
	t_hit			v_hit;
	char			v_xshift;
	t_dvector		v_step;
	double			wall_dist;
}				t_ray;

typedef struct s_vars	t_vars;

struct			s_vars
{
	void		*mlx;
	void		*win;
	void		(*pixel_put_ft)(t_vars const *v, unsigned const x,
			unsigned const y, t_color const color);
	t_bmp_color	**first_image_colors;
	t_img_data	img;
	t_uvector	res;
	t_textures	textures;
	t_map		map;
	t_player	player;
	double		project_dist;
	t_keys		keys;
	double		weapon_state;
};

#endif
