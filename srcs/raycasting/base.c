/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:12:55 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/04 13:26:39 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "minilibx.h"

void	get_angle_orientation(t_ray *ray)
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

void	set_ray_distance(t_hit *hit, double const angle, t_vars *v)
{
	hit->distance = sqrt((v->player.x - hit->x)
			* (v->player.x - hit->x)
			+ (v->player.y - hit->y) * (v->player.y - hit->y));
	hit->distance *= cos(fabs(v->player.angle - angle));
}

void	search_sprites1(t_ray *ray, t_vars *v)
{
	char hbool = 1;
	char vbool = 1;
	search_h_sprite_hit(ray, v);
	search_v_sprite_hit(ray, v);
	while (hbool || vbool)
	{
		hbool = 0;
		vbool = 0;
		if (ray->h_hit.distance < 9999999999 && (ray->v_hit.distance > 9999999999
					|| ray->h_hit.distance > ray->v_hit.distance))
		{
			ray->h_hit.height = BLOCK_SIZE / ray->h_hit.distance * v->project_dist;
			draw_col(ray->col, &ray->h_hit, &v->textures.sprite, v);
			search_h_sprite_hit(ray, v);
			hbool = 1;
		}
		else if (ray->v_hit.distance < 9999999999)
		{
			if (ray->v_hit.distance < ray->wall_dist)
			{
				ray->v_hit.height = BLOCK_SIZE / ray->v_hit.distance * v->project_dist;
				draw_col(ray->col, &ray->v_hit, &v->textures.sprite, v);
			}
			search_v_sprite_hit(ray, v);
			vbool = 1;
		}
	}
}

void	search_sprites2(t_ray *ray, t_vars *v)
{
	char hbool = 1;
	char vbool = 1;
	search_h_sprite_hit(ray, v);
	search_v_sprite_hit(ray, v);
	while (hbool || vbool)
	{
		hbool = 0;
		vbool = 0;
		if (ray->h_hit.distance < 9999999999 && (ray->v_hit.distance > 9999999999
					|| ray->h_hit.distance > ray->v_hit.distance))
		{
			if (ray->h_hit.distance < ray->wall_dist)
			{
				ray->h_hit.height = BLOCK_SIZE / ray->h_hit.distance * v->project_dist;
				draw_col(ray->col, &ray->h_hit, &v->textures.sprite, v);
			}
			search_h_sprite_hit(ray, v);
			hbool = 1;
		}
		else if (ray->v_hit.distance < 9999999999)
		{
			ray->v_hit.height = BLOCK_SIZE / ray->v_hit.distance * v->project_dist;
			draw_col(ray->col, &ray->v_hit, &v->textures.sprite, v);
			search_v_sprite_hit(ray, v);
			vbool = 1;
		}
	}
}

void	cast_ray(t_ray *ray, t_vars *v)
{
	get_angle_orientation(ray);
	search_h_wall_hit(ray, v);
	search_v_wall_hit(ray, v);
	if (ray->h_hit.distance < ray->v_hit.distance)
	{
		ray->wall_dist = ray->h_hit.distance;
		ray->h_hit.height = BLOCK_SIZE / ray->h_hit.distance * v->project_dist;
		ray->h_hit.offset = (int)ray->h_hit.x % BLOCK_SIZE;
		if (ray->orientation[0] == SOUTH)
		{
			ray->h_hit.offset = abs(ray->h_hit.offset - (BLOCK_SIZE - 1));
			draw_col(ray->col, &ray->h_hit, &v->textures.south, v);
		}
		else
			draw_col(ray->col, &ray->h_hit, &v->textures.north, v);
		search_sprites1(ray, v);
	}
	else
	{
		ray->wall_dist = ray->v_hit.distance;
		ray->v_hit.height = BLOCK_SIZE / ray->v_hit.distance * v->project_dist;
		ray->v_hit.offset = (int)ray->v_hit.y % BLOCK_SIZE;
		if (ray->orientation[1] == WEST)
		{
			ray->v_hit.offset = abs(ray->v_hit.offset - (BLOCK_SIZE - 1));
			draw_col(ray->col, &ray->v_hit, &v->textures.west, v);
		}
		else
			draw_col(ray->col, &ray->v_hit, &v->textures.east, v);
		search_sprites2(ray, v);
	}
}

void	cast_rays(t_vars *v)
{
	t_ray		ray;

	ray.angle = normalize_angle(v->player.angle + v->player.fov / 2);
	ray.col = 0;
	while (ray.col < v->res.x)
	{
		cast_ray(&ray, v);
		ray.angle = normalize_angle(ray.angle - v->player.fov / v->res.x);
		ray.col++;
	}
}
