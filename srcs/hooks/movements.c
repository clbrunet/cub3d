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

static void	move(t_vars *v, double x, double y)
{
	if ((M_PI_4 < v->player.angle && v->player.angle < M_PI - M_PI_4)
			|| (M_PI + M_PI_4 < v->player.angle
				&& v->player.angle < 7 * M_PI_4))
	{
		if (!is_wall(v, v->player.pos.x, y)
				&& !is_sprite_move(v, v->player.pos.x, y))
			v->player.pos.y = y;
		if (!is_wall(v, x, v->player.pos.y)
				&& !is_sprite_move(v, x, v->player.pos.y))
			v->player.pos.x = x;
	}
	else
	{
		if (!is_wall(v, x, v->player.pos.y)
				&& !is_sprite_move(v, x, v->player.pos.y))
			v->player.pos.x = x;
		if (!is_wall(v, v->player.pos.x, y)
				&& !is_sprite_move(v, v->player.pos.x, y))
			v->player.pos.y = y;
	}
}

char		two_axis_movements(t_vars *v)
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

void		one_axis_movements(t_vars *v)
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
