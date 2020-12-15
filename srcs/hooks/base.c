/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:30:53 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/14 08:16:36 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "raycasting.h"
#include "draw.h"

int		keypress_hook(int keycode, t_vars *v)
{
	if (keycode == ESC)
		end(v);
	else if (keycode == LEFT)
		v->keys.left = 1;
	else if (keycode == RIGHT)
		v->keys.right = 1;
	else if (keycode == Z)
		v->keys.z = 1;
	else if (keycode == S)
		v->keys.s = 1;
	else if (keycode == Q)
		v->keys.q = 1;
	else if (keycode == D)
		v->keys.d = 1;
	else
		return (keypress_hook2(keycode, v));
	return (0);
}

int		keypress_hook2(int keycode, t_vars *v)
{
	if (keycode == LSHIFT)
	{
		if (!v->keys.lshift)
			v->player.speed *= 2;
		v->keys.lshift = 1;
	}
	else if (keycode == UP)
		v->keys.up = 1;
	else if (keycode == DOWN)
		v->keys.down = 1;
	else if (keycode == LCTRL)
	{
		if (!v->keys.lctrl)
		{
			v->player.height -= 30;
			v->player.speed /= 2;
		}
		v->keys.lctrl = 1;
	}
	else if (keycode == F)
		v->keys.f = 1;
	return (0);
}

int		keyrelease_hook(int keycode, t_vars *v)
{
	if (keycode == LEFT)
		v->keys.left = 0;
	else if (keycode == RIGHT)
		v->keys.right = 0;
	else if (keycode == Z)
		v->keys.z = 0;
	else if (keycode == Q)
		v->keys.q = 0;
	else if (keycode == S)
		v->keys.s = 0;
	else if (keycode == D)
		v->keys.d = 0;
	else if (keycode == LSHIFT)
	{
		v->player.speed /= 2;
		v->keys.lshift = 0;
	}
	else if (keycode == UP)
		v->keys.up = 0;
	else if (keycode == DOWN)
		v->keys.down = 0;
	return (keyrelease_hook2(keycode, v));
}

int		keyrelease_hook2(int keycode, t_vars *v)
{
	if (keycode == LCTRL)
	{
		v->player.height += 30;
		v->player.speed *= 2;
		v->keys.lctrl = 0;
	}
	else if (keycode == F)
		v->keys.f = 0;
	return (0);
}

int		loop_hook(t_vars *v)
{
	update(v);
	cast_rays(v);
	draw_hud(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	return (0);
}
