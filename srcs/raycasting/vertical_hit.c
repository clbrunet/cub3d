/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:40:27 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/09 06:52:00 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	set_v_first_hit(t_ray *ray, t_vars const *v)
{
	ray->v_hit.x = ((int)v->player.x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
	if (ray->orientation[1] == EAST)
		ray->v_hit.x += BLOCK_SIZE;
	ray->v_hit.y = v->player.y + (v->player.x - ray->v_hit.x) * tan(ray->angle);
}

static void	set_v_step(t_ray *ray)
{
	ray->v_step.x = BLOCK_SIZE;
	if (ray->orientation[1] == WEST)
		ray->v_step.x *= -1;
	ray->v_step.y = BLOCK_SIZE * tan(ray->angle);
	if ((ray->orientation[0] == NORTH && ray->v_step.y > 0)
			|| (ray->orientation[0] == SOUTH && ray->v_step.y < 0))
		ray->v_step.y *= -1;
}

void		search_v_wall_hit(t_ray *ray, t_vars *v)
{
	ray->v_hit.distance = 999999999999999;
	if (ray->orientation[1] == WEST)
		ray->v_xshift = -1;
	else
		ray->v_xshift = 0;
	set_v_first_hit(ray, v);
	set_v_step(ray);
	if (!is_in_map(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y))
		return ;
	else if (is_wall(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y))
		return (set_ray_distance(&ray->v_hit, ray->angle, v));
	ray->v_hit.x += ray->v_step.x;
	ray->v_hit.y += ray->v_step.y;
	while (is_in_map(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y))
	{
		if (is_wall(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y))
			return (set_ray_distance(&ray->v_hit, ray->angle, v));
		ray->v_hit.x += ray->v_step.x;
		ray->v_hit.y += ray->v_step.y;
	}
}

char		search_v_sprite_hit(t_ray *ray, t_vars *v)
{
	ray->v_hit.distance = 999999999999999;
	ray->v_hit.x -= ray->v_step.x;
	ray->v_hit.y -= ray->v_step.y;
	while (((ray->orientation[1] == EAST && ray->v_hit.x > v->player.x)
				|| (ray->orientation[1] == WEST && ray->v_hit.x < v->player.x))
			&& !is_in_map(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y))
	{
		ray->v_hit.x -= ray->v_step.x;
		ray->v_hit.y -= ray->v_step.y;
	}
	while (!((ray->orientation[1] == EAST && ray->v_hit.x < v->player.x)
				|| (ray->orientation[1] == WEST && ray->v_hit.x > v->player.x)
				|| !is_in_map(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y)))
	{
		if (is_sprite(v, ray->v_hit.x + ray->v_xshift, ray->v_hit.y))
		{
			t_dvector center;
			t_dvector t[2];
			center.x = ((((int)ray->v_hit.x + ray->v_xshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			center.y = (((int)ray->v_hit.y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * BLOCK_SIZE_2;
			t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * BLOCK_SIZE_2;
			t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * BLOCK_SIZE_2;
			t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * BLOCK_SIZE_2;
			if (get_line_intersection(t[0].x, t[0].y, t[1].x, t[1].y, v->player.x, v->player.y,
						ray->v_hit.x + ray->v_step.x, ray->v_hit.y + ray->v_step.y, &center.x, &center.y))
			{
				ray->v_hit.offset = (int)dist(t[0], center.x, center.y);
				ray->v_hit.distance = sqrt((v->player.x - center.x) * (v->player.x - center.x)
						+ (v->player.y - center.y) * (v->player.y - center.y));
				ray->v_hit.distance *= cos(fabs(v->player.angle - ray->angle));
				return (1);
			}
		}
		ray->v_hit.x -= ray->v_step.x;
		ray->v_hit.y -= ray->v_step.y;
	}
	return (0);
}
