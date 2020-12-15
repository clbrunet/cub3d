/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:51:27 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/13 10:07:54 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "raycasting.h"

static char	is_sprite_move(t_vars *v, unsigned x, unsigned y)
{
	x >>= BLOCK_SIZE_BIT;
	y >>= BLOCK_SIZE_BIT;
	if (!(v->map.grid[y][x] == 'h' || v->map.grid[y][x] == 'm'))
		return (0);
	if (v->map.grid[y][x] == 'h' && v->player.health < 5)
	{
		v->map.grid[y][x] = 'e';
		v->player.health++;
		return (0);
	}
	if (v->map.grid[y][x] == 'm')
		v->player.health--;
	if (v->player.health == 0)
	{
		ft_putendl_fd("You died", 1);
		end(v);
	}
	return (1);
}

static void	move(t_vars *v, double x, double y)
{
	if ((M_PI_4 < v->player.angle && v->player.angle < M_PI - M_PI_4)
			|| (M_PI + M_PI_4 < v->player.angle
				&& v->player.angle < 7 * M_PI_4))
	{
		if (!is_real_wall(v, v->player.pos.x, y)
				&& !is_sprite_move(v, v->player.pos.x, y))
			v->player.pos.y = y;
		if (!is_real_wall(v, x, v->player.pos.y)
				&& !is_sprite_move(v, x, v->player.pos.y))
			v->player.pos.x = x;
	}
	else
	{
		if (!is_real_wall(v, x, v->player.pos.y)
				&& !is_sprite_move(v, x, v->player.pos.y))
			v->player.pos.x = x;
		if (!is_real_wall(v, v->player.pos.x, y)
				&& !is_sprite_move(v, v->player.pos.x, y))
			v->player.pos.y = y;
	}
}

static char	two_axis_movements(t_vars *v)
{
	if (v->keys.z && !v->keys.s && v->keys.q && !v->keys.d)
		move(v, v->player.pos.x + cos(fix_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2.5),
				v->player.pos.y - sin(fix_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2.5));
	else if (v->keys.z && !v->keys.s && v->keys.d && !v->keys.q)
		move(v, v->player.pos.x + cos(fix_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2.5),
				v->player.pos.y - sin(fix_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2.5));
	else if (v->keys.s && !v->keys.z && v->keys.q && !v->keys.d)
		move(v, v->player.pos.x - cos(fix_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2),
				v->player.pos.y + sin(fix_angle(v->player.angle - M_PI_4))
				* (v->player.speed / 3 * 2));
	else if (v->keys.s && !v->keys.z && v->keys.d && !v->keys.q)
		move(v, v->player.pos.x - cos(fix_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2),
				v->player.pos.y + sin(fix_angle(v->player.angle + M_PI_4))
				* (v->player.speed / 3 * 2));
	else
		return (0);
	return (1);
}

static void	one_axis_movements(t_vars *v)
{
	if (v->keys.z && !v->keys.s)
		move(v, v->player.pos.x + cos(v->player.angle) * v->player.speed,
				v->player.pos.y - sin(v->player.angle) * v->player.speed);
	else if (v->keys.s && !v->keys.z)
		move(v, v->player.pos.x - cos(v->player.angle)
				* (v->player.speed / 3 * 2),
				v->player.pos.y + sin(v->player.angle)
				* (v->player.speed / 3 * 2));
	else if (v->keys.q && !v->keys.d)
		move(v, v->player.pos.x + cos(fix_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2),
				v->player.pos.y - sin(fix_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2));
	else if (v->keys.d && !v->keys.q)
		move(v, v->player.pos.x - cos(fix_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2),
				v->player.pos.y + sin(fix_angle(v->player.angle + M_PI_2))
				* (v->player.speed / 3 * 2));
}

void		update(t_vars *v)
{
	if (v->keys.left)
		v->player.angle = fix_angle(v->player.angle
				+ deg_to_rad(v->player.speed / 3));
	if (v->keys.right)
		v->player.angle = fix_angle(v->player.angle
				- deg_to_rad(v->player.speed / 3));
	if (v->keys.up)
		if (v->player.height + v->player.speed + 30 < v->res.y)
			v->player.height += round(v->player.speed);
	if (v->keys.down)
		if ((signed)v->player.height - v->player.speed - 30 > 0)
			v->player.height -= round(v->player.speed);
	if (!two_axis_movements(v))
		one_axis_movements(v);
	if (v->weapon_state > 0.2 || v->keys.f)
	{
		if (v->weapon_state > 5)
			kill_monster(v);
		v->weapon_state += 0.5;
		if (v->weapon_state >= 5.9)
			v->weapon_state = 0;
	}
}
