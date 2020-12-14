/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:12:55 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 15:05:07 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "draw.h"

static void	get_angle_orientation(t_ray *ray)
{
	if (ray->angle < M_PI)
		ray->orientation[0] = NORTH;
	else
		ray->orientation[0] = SOUTH;
	if (M_PI_2 < ray->angle && ray->angle < 3 * M_PI_2)
		ray->orientation[1] = WEST;
	else
		ray->orientation[1] = EAST;
}

void		set_sprite_widthline(t_dline *line, t_dvector *center,
		t_vars const *v)
{
	line->p1.x = center->x + cos(fix_angle(v->player.angle + M_PI_2))
		* BLOCK_SIZE_2;
	line->p1.y = center->y - sin(fix_angle(v->player.angle + M_PI_2))
		* BLOCK_SIZE_2;
	line->p2.x = center->x + cos(fix_angle(v->player.angle - M_PI_2))
		* BLOCK_SIZE_2;
	line->p2.y = center->y - sin(fix_angle(v->player.angle - M_PI_2))
		* BLOCK_SIZE_2;
}

static void	search_sprites(t_ray *ray, t_vars const *v)
{
	char h_bool;
	char v_bool;

	h_bool = search_h_sprite_hit(ray, v);
	v_bool = search_v_sprite_hit(ray, v);
	while (h_bool || v_bool)
	{
		h_bool = 0;
		v_bool = 0;
		if (ray->h_hit.distance < 9999999999 && (ray->v_hit.distance
					> 9999999999 || ray->h_hit.distance > ray->v_hit.distance))
		{
			if (ray->h_hit.distance < ray->wall_dist)
				draw_sprite(ray->col, &ray->h_hit, &v->textures.sprite, v);
			h_bool = 1;
			search_h_sprite_hit(ray, v);
		}
		else if (ray->v_hit.distance < 9999999999)
		{
			if (ray->v_hit.distance < ray->wall_dist)
				draw_sprite(ray->col, &ray->v_hit, &v->textures.sprite, v);
			v_bool = 1;
			search_v_sprite_hit(ray, v);
		}
	}
}

static void	cast_ray(t_ray *ray, t_vars const *v)
{
	get_angle_orientation(ray);
	search_h_wall_hit(ray, v);
	search_v_wall_hit(ray, v);
	if (ray->h_hit.distance < ray->v_hit.distance)
		display_h_wall(ray, v);
	else
		display_v_wall(ray, v);
	search_sprites(ray, v);
}

void		cast_rays(t_vars const *v)
{
	t_ray		ray;

	ray.angle = fix_angle(v->player.angle + v->player.fov / 2);
	ray.col = 0;
	while (ray.col < v->res.x)
	{
		cast_ray(&ray, v);
		ray.angle = fix_angle(ray.angle - v->player.fov / v->res.x);
		ray.col++;
	}
}
