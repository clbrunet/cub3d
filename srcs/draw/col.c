/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:59:21 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/12 14:51:23 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void		draw_only_wall(unsigned const col, t_hit const *hit,
		t_texture const *texture, t_vars const *v)
{
	unsigned	texture_col;
	t_color		color;
	unsigned	height_res_diff_2;
	unsigned	y;

	texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width);
	height_res_diff_2 = (hit->height - v->res.y) / 2;
	y = 0;
	while (y < v->res.y)
	{
		color.full = mlx_img_pixel_get_value(texture->img, texture_col,
				(y + height_res_diff_2) * texture->height / hit->height);
		if (!color.bytes.alpha)
			(*v->pixel_put_ft)(v, col, y, color);
		y++;
	}
}

static void		draw_ceilling(unsigned const col, unsigned const height,
		t_vars const *v)
{
	unsigned	y;

	y = 0;
	while (y < height)
	{
		(*v->pixel_put_ft)(v, col, y, v->colors.ceilling);
		y++;
	}
}

void			draw_wall(unsigned const col, t_hit const *hit,
		t_texture const *texture, t_vars const *v)
{
	unsigned	texture_col;
	t_color		color;
	unsigned	y;
	unsigned	i;

	texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width);
	y = v->res.y / 2 - hit->height / 2;
	i = 0;
	while (i < hit->height)
	{
		color.full = mlx_img_pixel_get_value(texture->img, texture_col,
				i * texture->height / hit->height);
		if (!color.bytes.alpha)
			(*v->pixel_put_ft)(v, col, y, color);
		y++;
		i++;
	}
}

static void		draw_floor(unsigned const col, unsigned y, t_vars const *v)
{
	while (y < v->res.y)
	{
		(*v->pixel_put_ft)(v, col, y, v->colors.floor);
		y++;
	}
}

void			draw_col(unsigned const col, t_hit const *hit,
		t_texture const *texture, t_vars const *v)
{
	if (hit->height > v->res.y)
		return (draw_only_wall(col, hit, texture, v));
	draw_ceilling(col, v->res.y / 2 - hit->height / 2, v);
	draw_wall(col, hit, texture, v);
	draw_floor(col, v->res.y / 2 + hit->height / 2, v);
}
