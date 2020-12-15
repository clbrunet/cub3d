/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 07:51:56 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 08:58:28 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	search_h_monster(t_ray *ray, t_vars const *v)
{
	ray->h_hit.distance = 999999999999999;
	set_h_first_hit_and_step(ray, v);
	if (ray->orientation[0] == NORTH)
		ray->h_hit.pos.y--;
	if (!is_in_map(v, ray->h_hit.pos.x, ray->h_hit.pos.y)
			|| is_wall(v, ray->h_hit.pos.x, ray->h_hit.pos.y))
		return ;
	else if (is_monster(v, ray->h_hit.pos.x, ray->h_hit.pos.y))
	{
		ray->h_hit.distance = playerdist_fisheyeless(ray->h_hit.pos,
				ray->angle, v);
		return ;
	}
	ray->h_hit.pos = dvectoradd(ray->h_hit.pos, ray->h_step);
	while (is_in_map(v, ray->h_hit.pos.x, ray->h_hit.pos.y)
			&& !is_wall(v, ray->h_hit.pos.x, ray->h_hit.pos.y))
	{
		if (is_monster(v, ray->h_hit.pos.x, ray->h_hit.pos.y))
		{
			ray->h_hit.distance = playerdist_fisheyeless(ray->h_hit.pos,
					ray->angle, v);
			return ;
		}
		ray->h_hit.pos = dvectoradd(ray->h_hit.pos, ray->h_step);
	}
}

static void	search_v_monster(t_ray *ray, t_vars const *v)
{
	ray->v_hit.distance = 999999999999999;
	set_v_first_hit_and_step(ray, v);
	if (ray->orientation[1] == WEST)
		ray->v_hit.pos.x--;
	if (!is_in_map(v, ray->v_hit.pos.x, ray->v_hit.pos.y)
			|| is_wall(v, ray->v_hit.pos.x, ray->v_hit.pos.y))
		return ;
	else if (is_monster(v, ray->v_hit.pos.x, ray->v_hit.pos.y))
	{
		ray->v_hit.distance = playerdist_fisheyeless(ray->v_hit.pos,
				ray->angle, v);
		return ;
	}
	ray->v_hit.pos = dvectoradd(ray->v_hit.pos, ray->v_step);
	while (is_in_map(v, ray->v_hit.pos.x, ray->v_hit.pos.y)
			&& !is_wall(v, ray->v_hit.pos.x, ray->v_hit.pos.y))
	{
		if (is_monster(v, ray->v_hit.pos.x, ray->v_hit.pos.y))
		{
			ray->v_hit.distance = playerdist_fisheyeless(ray->v_hit.pos,
					ray->angle, v);
			return ;
		}
		ray->v_hit.pos = dvectoradd(ray->v_hit.pos, ray->v_step);
	}
}

void	kill_monster(t_vars const *v)
{
	t_ray	ray;

	ray.angle = v->player.angle;
	get_angle_orientation(&ray);
	search_h_monster(&ray, v);
	search_v_monster(&ray, v);
	if (ray.h_hit.distance > 9999999999 && ray.v_hit.distance > 9999999999)
		return ;
	if (ray.h_hit.distance < ray.v_hit.distance)
		v->map.grid[(int)ray.h_hit.pos.y >> BLOCK_SIZE_BIT]
			[(int)ray.h_hit.pos.x >> BLOCK_SIZE_BIT] = 'e';
	else
		v->map.grid[(int)ray.v_hit.pos.y >> BLOCK_SIZE_BIT]
			[(int)ray.v_hit.pos.x >> BLOCK_SIZE_BIT] = 'e';
}
