/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:38:58 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/09 12:02:31 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	set_h_first_hit(t_ray *ray, t_vars const *v)
{
	ray->h_hit.y = ((int)v->player.y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
	if (ray->orientation[0] == SOUTH)
		ray->h_hit.y += BLOCK_SIZE;
	ray->h_hit.x = v->player.x + (v->player.y - ray->h_hit.y) / tan(ray->angle);
}

static void	set_h_step(t_ray *ray)
{
	ray->h_step.y = BLOCK_SIZE;
	if (ray->orientation[0] == NORTH)
		ray->h_step.y = -BLOCK_SIZE;
	ray->h_step.x = BLOCK_SIZE / tan(ray->angle);
	if ((ray->orientation[1] == WEST && ray->h_step.x > 0)
			|| (ray->orientation[1] == EAST && ray->h_step.x < 0))
		ray->h_step.x *= -1;
}

void		search_h_wall_hit(t_ray *ray, t_vars *v)
{
	ray->h_hit.distance = 999999999999999;
	if (ray->orientation[0] == NORTH)
		ray->h_yshift = -1;
	else
		ray->h_yshift = 0;
	set_h_first_hit(ray, v);
	set_h_step(ray);
	if (!is_in_map(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift))
		return ;
	else if (is_wall(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift))
		return (set_ray_distance(&ray->h_hit, ray->angle, v));
	ray->h_hit.x += ray->h_step.x;
	ray->h_hit.y += ray->h_step.y;
	while (is_in_map(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift))
	{
		if (is_wall(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift))
			return (set_ray_distance(&ray->h_hit, ray->angle, v));
		ray->h_hit.x += ray->h_step.x;
		ray->h_hit.y += ray->h_step.y;
	}
}

char		search_h_sprite_hit(t_ray *ray, t_vars *v)
{
	ray->h_hit.distance = 999999999999999;
	ray->h_hit.x -= ray->h_step.x;
	ray->h_hit.y -= ray->h_step.y;
	while (((ray->orientation[0] == NORTH && ray->h_hit.y < v->player.y)
				|| (ray->orientation[0] == SOUTH && ray->h_hit.y > v->player.y))
			&& !is_in_map(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift))
	{
		ray->h_hit.x -= ray->h_step.x;
		ray->h_hit.y -= ray->h_step.y;
	}
	while (!((ray->orientation[0] == NORTH && ray->h_hit.y > v->player.y)
				|| (ray->orientation[0] == SOUTH && ray->h_hit.y < v->player.y)
				|| !is_in_map(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift)))
	{
		if (is_sprite(v, ray->h_hit.x, ray->h_hit.y + ray->h_yshift))
		{
			t_dvector center;
			t_dvector t[2];
			center.x = (((int)ray->h_hit.x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			center.y = ((((int)ray->h_hit.y + ray->h_yshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * BLOCK_SIZE_2;
			t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * BLOCK_SIZE_2;
			t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * BLOCK_SIZE_2;
			t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * BLOCK_SIZE_2;
			if (get_line_intersection(t[0].x, t[0].y, t[1].x, t[1].y, v->player.x, v->player.y,
						ray->h_hit.x + ray->h_step.x, ray->h_hit.y + ray->h_step.y, &center.x, &center.y))
			{
				ray->h_hit.offset = (int)dist(t[0], center.x, center.y);
				ray->h_hit.distance = sqrt((v->player.x - center.x) * (v->player.x - center.x)
						+ (v->player.y - center.y) * (v->player.y - center.y));
				ray->h_hit.distance *= cos(fabs(v->player.angle - ray->angle));
				return (1);
			}
		}
		ray->h_hit.x -= ray->h_step.x;
		ray->h_hit.y -= ray->h_step.y;
	}
	return (0);
}
