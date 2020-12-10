/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:02:01 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/08 14:50:18 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include "raycasting.h"

int		keypress_hook(int keycode, t_vars *v)
{
	/* printf("keycode: %i\n", keycode); */
	if (keycode == ESC)
		exit(0);
	else if (keycode == LEFT)
		v->keys_down.left = 1;
	else if (keycode == RIGHT)
		v->keys_down.right = 1;
	else if (keycode == Z)
		v->keys_down.z = 1;
	else if (keycode == S)
		v->keys_down.s = 1;
	else if (keycode == Q)
		v->keys_down.q = 1;
	else if (keycode == D)
		v->keys_down.d = 1;
	else if (keycode == SHIFT)
	{
		if (!v->keys_down.shift)
			v->player.speed *= 2;
		v->keys_down.shift = 1;
	}
	/* print_keys(&v->keys_down); */
	return (1);
}

int		keyrelease_hook(int keycode, t_vars *v)
{
	if (keycode == LEFT)
		v->keys_down.left = 0;
	else if (keycode == RIGHT)
		v->keys_down.right = 0;
	else if (keycode == Z)
		v->keys_down.z = 0;
	else if (keycode == Q)
		v->keys_down.q = 0;
	else if (keycode == S)
		v->keys_down.s = 0;
	else if (keycode == D)
		v->keys_down.d = 0;
	else if (keycode == SHIFT)
	{
		v->player.speed /= 2;
		v->keys_down.shift = 0;
	}
	return (1);
}

void	move(t_vars *v, double x, double y)
{
	if ((M_PI_4 < v->player.angle && v->player.angle < M_PI - M_PI_4)
			|| (M_PI + M_PI_4 < v->player.angle && v->player.angle < 7 * M_PI_4))
	{
		if (!is_wall(v, v->player.x, y) && !is_sprite(v, v->player.x, y))
			v->player.y = y;
		if (!is_wall(v, x, v->player.y) && !is_sprite(v, x, v->player.y))
			v->player.x = x;
	}
	else
	{
		if (!is_wall(v, x, v->player.y) && !is_sprite(v, x, v->player.y))
			v->player.x = x;
		if (!is_wall(v, v->player.x, y) && !is_sprite(v, v->player.x, y))
			v->player.y = y;
	}
}

void	edit(t_vars *v)
{
	if (v->keys_down.left)
		v->player.angle = normalize_angle(v->player.angle
				+ deg_to_rad(v->player.speed / 3));
	if (v->keys_down.right)
		v->player.angle = normalize_angle(v->player.angle
				- deg_to_rad(v->player.speed / 3));
	if (v->keys_down.z && !v->keys_down.s && v->keys_down.q && !v->keys_down.d)
		move(v, v->player.x + cos(normalize_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2.5),
				v->player.y - sin(normalize_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2.5));
	else if (v->keys_down.z && !v->keys_down.s
			&& v->keys_down.d && !v->keys_down.q)
		move(v, v->player.x + cos(normalize_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2.5),
				v->player.y - sin(normalize_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2.5));
	else if (v->keys_down.s && !v->keys_down.z
			&& v->keys_down.q && !v->keys_down.d)
		move(v, v->player.x - cos(normalize_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2),
				v->player.y + sin(normalize_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2));
	else if (v->keys_down.s && !v->keys_down.z
			&& v->keys_down.d && !v->keys_down.q)
		move(v, v->player.x - cos(normalize_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2),
				v->player.y + sin(normalize_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2));
	else if (v->keys_down.z && !v->keys_down.s)
		move(v, v->player.x + cos(v->player.angle) * v->player.speed,
				v->player.y - sin(v->player.angle) * v->player.speed);
	else if (v->keys_down.s && !v->keys_down.z)
		move(v, v->player.x - cos(v->player.angle) * (v->player.speed / 3 * 2),
				v->player.y + sin(v->player.angle) * (v->player.speed / 3 * 2));
	else if (v->keys_down.q && !v->keys_down.d)
		move(v, v->player.x + cos(normalize_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2),
				v->player.y - sin(normalize_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2));
	else if (v->keys_down.d && !v->keys_down.q)
		move(v, v->player.x - cos(normalize_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2),
				v->player.y + sin(normalize_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2));
}

int		loop_hook(t_vars *v)
{
	/* mlx_clear_img(v->img, v->res.x, v->res.y); */
	edit(v);
	cast_rays(v);
	/* draw_minimap(v); */
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	/* exit(0); */
	return (0);
}

void	initialize_keys_down(t_keys *keys_down)
{
	keys_down->left = 0;
	keys_down->right = 0;
	keys_down->z = 0;
	keys_down->q = 0;
	keys_down->s = 0;
	keys_down->d = 0;
}

void	initialize_mlx(t_vars *v)
{
	if (!(v->win = mlx_new_window(v->mlx, v->res.x, v->res.y,
					"Cub3D")))
		error("Window creation failed", v, ERROR);
	if (!(v->img.img = mlx_new_image(v->mlx, v->res.x, v->res.y)))
		error("Image creation failed", v, ERROR);
	v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bits_per_pixel,
			&v->img.line_length, &v->img.endian);
	mlx_loop_hook(v->mlx, &loop_hook, v);
	initialize_keys_down(&v->keys_down);
	mlx_hook(v->win, KeyPress, KeyPressMask, &keypress_hook, v);
	mlx_hook(v->win, KeyRelease, KeyReleaseMask, &keyrelease_hook, v);
}
