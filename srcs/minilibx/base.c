/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:02:01 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/01 11:02:01 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include "raycasting.h"

int		keypress_hook(int keycode, t_vars *v)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == LEFT)
		v->keys_down.left = 1;
	if (keycode == RIGHT)
		v->keys_down.right = 1;
	if (keycode == W)
		v->keys_down.w = 1;
	if (keycode == S)
		v->keys_down.s = 1;
	if (keycode == A)
	{
		printf("AAAAAAAAAa\n\n\n\nAAAAAAAAAAAAa\n\n\n");
		v->keys_down.a = 1;
	}
	if (keycode == D)
		v->keys_down.d = 1;
	print_keys(&v->keys_down);
	return (1);
}

int		keyrelease_hook(int keycode, t_vars *v)
{
	if (keycode == LEFT)
		v->keys_down.left = 0;
	if (keycode == RIGHT)
		v->keys_down.right = 0;
	if (keycode == W)
		v->keys_down.w = 0;
	if (keycode == S)
		v->keys_down.s = 0;
	if (keycode == A)
		v->keys_down.a = 0;
	if (keycode == D)
		v->keys_down.d = 0;
	return (1);
}

void	move(t_vars *v)
{
	if (v->keys_down.left)
		v->player.angle = normalize_angle(v->player.angle + deg_to_rad(2));
	if (v->keys_down.right)
		v->player.angle = normalize_angle(v->player.angle - deg_to_rad(2));
	if (v->keys_down.w && !v->keys_down.s && v->keys_down.a && !v->keys_down.d)
	{
		v->player.x += cos(normalize_angle(v->player.angle + M_PI_4)) * 6;
		v->player.y -= sin(normalize_angle(v->player.angle + M_PI_4)) * 6;
	}
	else if (v->keys_down.w && !v->keys_down.s
			&& v->keys_down.d && !v->keys_down.a)
	{
		v->player.x += cos(normalize_angle(v->player.angle - M_PI_4)) * 6;
		v->player.y -= sin(normalize_angle(v->player.angle - M_PI_4)) * 6;
	}
	else if (v->keys_down.s && !v->keys_down.w
			&& v->keys_down.a && !v->keys_down.d)
	{
		v->player.x -= cos(normalize_angle(v->player.angle - M_PI_4)) * 6;
		v->player.y += sin(normalize_angle(v->player.angle - M_PI_4)) * 6;
	}
	else if (v->keys_down.s && !v->keys_down.w
			&& v->keys_down.d && !v->keys_down.d)
	{
		v->player.x -= cos(normalize_angle(v->player.angle + M_PI_4)) * 6;
		v->player.y += sin(normalize_angle(v->player.angle + M_PI_4)) * 6;
	}
	else if (v->keys_down.w && !v->keys_down.s)
	{
		v->player.x += cos(v->player.angle) * 6;
		v->player.y -= sin(v->player.angle) * 6;
	}
	else if (v->keys_down.s && !v->keys_down.w)
	{
		v->player.x -= cos(v->player.angle) * 6;
		v->player.y += sin(v->player.angle) * 6;
	}
	else if (v->keys_down.a && !v->keys_down.d)
	{
		v->player.x += cos(v->player.angle + M_PI_2) * 4;
		v->player.y -= sin(v->player.angle + M_PI_2) * 4;
	}
	else if (v->keys_down.d && !v->keys_down.a)
	{
		v->player.x -= cos(v->player.angle + M_PI_2) * 4;
		v->player.y += sin(v->player.angle + M_PI_2) * 4;
	}
}

int		loop_hook(t_vars *v)
{
	mlx_clear_img(v->img, v->res.x, v->res.y);
	move(v);
	cast_rays(v);
	draw_minimap(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	return (0);
}

void	initialize_keys_down(t_keys *keys_down)
{
	keys_down->left = 0;
	keys_down->right = 0;
	keys_down->w = 0;
	keys_down->s = 0;
	keys_down->a = 0;
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
