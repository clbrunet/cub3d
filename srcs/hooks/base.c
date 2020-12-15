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

void	update(t_vars *v)
{
	if (v->keys.left)
		v->player.angle = fix_angle(v->player.angle
				+ deg_to_rad(v->player.speed / 3));
	if (v->keys.right)
		v->player.angle = fix_angle(v->player.angle
				- deg_to_rad(v->player.speed / 3));
	if (v->keys.up)
		if (v->player.height + v->player.speed + 30 < v->res.y)
		v->player.height += v->player.speed;
	if (v->keys.down)
		if ((signed)v->player.height - v->player.speed - 30 > 0)
			v->player.height -= v->player.speed;
	if (!two_axis_movements(v))
		one_axis_movements(v);
	if (v->weapon_state > 0.2 || v->keys.f)
	{
		if (v->weapon_state > 4)
			kill_monster(v);
		v->weapon_state += 0.5;
		if (v->weapon_state >= 4.9)
			v->weapon_state = 0;
	}
}

int		loop_hook(t_vars *v)
{
	update(v);
	cast_rays(v);
	draw_hud(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	return (0);
}
