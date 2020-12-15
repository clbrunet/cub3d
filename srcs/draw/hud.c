/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:27:28 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 15:01:08 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_health(t_vars const *v, unsigned tlx, unsigned tly,
		unsigned side)
{
	t_color		color;
	unsigned	x;
	unsigned	y;

	color.full = BLACK;
	y = tly;
	while (y < tly + side)
	{
		x = tlx;
		while (x < tlx + side)
		{
			color.full = mlx_img_pixel_get_value(&v->textures.health.img,
					(double)(x - tlx) / (double)(side
						/ (double)v->textures.health.width),
					(double)(y - tly) / (double)(side
						/ (double)v->textures.health.height));
			if (!color.bytes.alpha)
				(*v->pixel_put_ft)(v, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_health_bar(t_vars const *v)
{
	unsigned	y;
	unsigned	x;
	unsigned	i;
	unsigned	side;

	if (v->res.x / 12 - 10 > v->res.y / 6)
		side = v->res.y / 6;
	else
		side = v->res.x / 12 - 10;
	y = 4 * v->res.y / 5;
	x = 10;
	if (v->res.x < 500 || v->res.y < 500 || 5 * side + 50 > v->res.x / 2)
		return ;
	i = 0;
	while (i < v->player.health)
	{
		draw_health(v, x, y, side);
		x += side + 10;
		i++;
	}
}

static void	draw_weapon(t_vars const *v)
{
	t_color		color;
	unsigned	y;
	unsigned	x;

	y = v->res.y / 2;
	while (y < v->res.y)
	{
		x = v->res.x / 2;
		while (x < v->res.x)
		{
			color.full = mlx_img_pixel_get_value(&v->textures.weapon
					[(int)v->weapon_state].img,
					(double)(x - (double)v->res.x / 2) / ((double)v->res.x / 2
						/ (double)v->textures.weapon
						[(int)v->weapon_state].width),
					(double)(y - (double)v->res.y / 2) / ((double)v->res.y / 2
						/ (double)v->textures.weapon
						[(int)v->weapon_state].height));
			if (!color.bytes.alpha)
				(*v->pixel_put_ft)(v, x, y, color);
			x++;
		}
		y++;
	}
}

static void	draw_crosshair(t_vars const *v)
{
	t_color		color;
	unsigned	y;
	unsigned	x;

	if (v->res.x < 50 || v->res.y < 50)
		return ;
	color.full = WHITE;
	y = v->res.y / 2 - 10;
	x = v->res.x / 2 - 10;
	while (y < v->res.y / 2 + 10)
	{
		(*v->pixel_put_ft)(v, x, v->res.y / 2, color);
		(*v->pixel_put_ft)(v, v->res.x / 2, y, color);
		x++;
		y++;
	}
}

void		draw_hud(t_vars const *v)
{
	draw_health_bar(v);
	draw_crosshair(v);
	draw_weapon(v);
}
