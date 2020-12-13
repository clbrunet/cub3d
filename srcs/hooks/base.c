/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:30:53 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:30:53 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "raycasting.h"

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
	else if (keycode == SHIFT)
	{
		if (!v->keys.shift)
			v->player.speed *= 2;
		v->keys.shift = 1;
	}
	return (1);
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
	else if (keycode == SHIFT)
	{
		v->player.speed /= 2;
		v->keys.shift = 0;
	}
	return (1);
}

void	update(t_vars *v)
{
	if (v->keys.left)
		v->player.angle = fix_angle(v->player.angle
				+ deg_to_rad(v->player.speed / 3));
	if (v->keys.right)
		v->player.angle = fix_angle(v->player.angle
				- deg_to_rad(v->player.speed / 3));
	if (!two_axis_movements(v))
		one_axis_movements(v);
}

int		loop_hook(t_vars *v)
{
	update(v);
	cast_rays(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	return (0);
}
