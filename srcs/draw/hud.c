/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 20:27:28 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 07:30:21 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	draw_health(t_vars const *v, unsigned tlx, unsigned tly)
{
	t_color		color;
	unsigned	x;
	unsigned	y;

	color.full = BLACK;
	y = tly;
	while (y < tly + 64)
	{
		x = tlx;
		while (x < tlx + 64)
		{
			color.full = mlx_img_pixel_get_value(&v->textures.health.img,
					(double)(x - tlx) / (double)(64 / (double)v->textures.health.width),
					(double)(y - tly) / (double)(64 / (double)v->textures.health.height));
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

	if (v->res.x < 500 || v->res.y < 250)
		return ;
	y = v->res.y - 75;
	x = 10;
	i = 0;
	while (i < v->player.health)
	{
		draw_health(v, x, y);
		x += 74;
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
						/ (double)v->textures.weapon[(int)v->weapon_state].width),
					(double)(y - (double)v->res.y / 2) / ((double)v->res.y / 2
						/ (double)v->textures.weapon[(int)v->weapon_state].height));
			if (!color.bytes.alpha)
				(*v->pixel_put_ft)(v, x, y, color);
			x++;
		}
		y++;
	}
}

void		draw_hud(t_vars const *v)
{
	draw_health_bar(v);
	draw_weapon(v);
}
