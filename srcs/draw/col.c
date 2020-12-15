/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:59:21 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 14:39:40 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_wall(unsigned const col, t_hit const *hit,
		t_texture const *texture, t_vars const *v)
{
	unsigned	texture_col;
	t_color		color;
	int			y;
	unsigned	i;

	texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width);
	y = v->player.height - hit->height / 2;
	i = 0;
	while (i < hit->height)
	{
		if (y >= (signed)v->res.y)
			break ;
		if (y >= 0)
		{
			color.full = mlx_img_pixel_get_value(&texture->img, texture_col,
					i * texture->height / hit->height);
			color = fog(color, hit->distance, v);
			(*v->pixel_put_ft)(v, col, y, color);
		}
		y++;
		i++;
	}
}

void	draw_sprite(unsigned const col, t_hit const *hit, t_vars const *v)
{
	unsigned	texture_col;
	t_color		color;
	int			y;
	unsigned	i;
	t_texture	texture;

	get_sprite_data(&texture_col, &texture, hit, v);
	y = v->player.height - hit->height / 2;
	i = 0;
	while (i < hit->height)
	{
		if (y >= (signed)v->res.y)
			break ;
		if (y >= 0)
		{
			color.full = mlx_img_pixel_get_value(&texture.img, texture_col,
					i * texture.height / hit->height);
			color = fog(color, hit->distance, v);
			if (!color.bytes.alpha)
				(*v->pixel_put_ft)(v, col, y, color);
		}
		y++;
		i++;
	}
}

void	draw_floor(t_ray const *ray, t_hit const *hit, t_vars const *v)
{
	int			y;
	int			i;
	double		dist;
	t_dvector	inter;
	t_color		color;

	y = v->res.y / 2 + hit->height / 2;
	i = v->player.height + hit->height / 2;
	while (i < (signed)v->res.y)
	{
		dist = get_floor_data(y, ray, &inter, v);
		color.full = mlx_img_pixel_get_value(&v->textures.floor.img,
				(double)((int)inter.x % BLOCK_SIZE) / ((double)BLOCK_SIZE
					/ (double)v->textures.floor.width), (double)((int)inter.y
					% BLOCK_SIZE) / ((double)BLOCK_SIZE
						/ v->textures.floor.height));
		color = fog(color, dist, v);
		(*v->pixel_put_ft)(v, ray->col, y - (v->res.y / 2
					- v->player.height), color);
		y++;
		i++;
	}
}

void	draw_ceilling(t_ray const *ray, t_hit const *hit, t_vars const *v)
{
	int			y;
	int			i;
	double		dist;
	t_dvector	inter;
	t_color		color;

	y = v->res.y / 2 - hit->height / 2;
	i = v->player.height - hit->height / 2;
	while (i >= 0)
	{
		dist = get_ceilling_data(y, ray, &inter, v);
		color.full = mlx_img_pixel_get_value(&v->textures.ceilling.img,
				(double)((int)inter.x % BLOCK_SIZE) / ((double)BLOCK_SIZE
					/ v->textures.ceilling.width), (double)((int)inter.y
						% BLOCK_SIZE) / ((double)BLOCK_SIZE
							/ v->textures.ceilling.height));
		color = fog(color, dist, v);
		(*v->pixel_put_ft)(v, ray->col, y - (v->res.y / 2
					- v->player.height), color);
		y--;
		i--;
	}
}
