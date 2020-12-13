/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:40:27 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 14:41:54 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "draw.h"

static void	set_v_first_hit_and_step(t_ray *ray, t_vars const *v)
{
	ray->v_hit.pos.x = ((int)v->player.pos.x >> BLOCK_SIZE_BIT)
		<< BLOCK_SIZE_BIT;
	if (ray->orientation[1] == EAST)
		ray->v_hit.pos.x += BLOCK_SIZE;
	ray->v_hit.pos.y = v->player.pos.y + (v->player.pos.x - ray->v_hit.pos.x)
		* tan(ray->angle);
	ray->v_step.x = BLOCK_SIZE;
	if (ray->orientation[1] == WEST)
		ray->v_step.x *= -1;
	ray->v_step.y = BLOCK_SIZE * tan(ray->angle);
	if ((ray->orientation[0] == NORTH && ray->v_step.y > 0)
			|| (ray->orientation[0] == SOUTH && ray->v_step.y < 0))
		ray->v_step.y *= -1;
}

void		search_v_wall_hit(t_ray *ray, t_vars const *v)
{
	ray->v_hit.distance = 999999999999999;
	if (ray->orientation[1] == WEST)
		ray->v_xshift = -1;
	else
		ray->v_xshift = 0;
	set_v_first_hit_and_step(ray, v);
	if (!is_in_map(v, ray->v_hit.pos.x + ray->v_xshift, ray->v_hit.pos.y))
		return ;
	else if (is_wall(v, ray->v_hit.pos.x + ray->v_xshift, ray->v_hit.pos.y))
	{
		ray->v_hit.distance = playerdist_fisheyeless(ray->v_hit.pos,
				ray->angle, v);
		return ;
	}
	ray->v_hit.pos = dvectoradd(ray->v_hit.pos, ray->v_step);
	while (is_in_map(v, ray->v_hit.pos.x + ray->v_xshift, ray->v_hit.pos.y))
	{
		if (is_wall(v, ray->v_hit.pos.x + ray->v_xshift, ray->v_hit.pos.y))
		{
			ray->v_hit.distance = playerdist_fisheyeless(ray->v_hit.pos,
					ray->angle, v);
			return ;
		}
		ray->v_hit.pos = dvectoradd(ray->v_hit.pos, ray->v_step);
	}
}

void		display_v_wall(t_ray *ray, t_vars const *v)
{
	ray->wall_dist = ray->v_hit.distance;
	ray->v_hit.height = BLOCK_SIZE / ray->v_hit.distance * v->project_dist;
	ray->v_hit.offset = (int)ray->v_hit.pos.y % BLOCK_SIZE;
	if (ray->orientation[1] == WEST)
	{
		ray->v_hit.offset = abs((int)ray->v_hit.offset - (BLOCK_SIZE - 1));
		draw_col(ray->col, &ray->v_hit, &v->textures.west, v);
	}
	else
		draw_col(ray->col, &ray->v_hit, &v->textures.east, v);
}

static char	check_in_v_sprite_width(t_ray *ray, t_vars const *v)
{
	t_dvector	center;
	t_dline		line;
	t_dvector	inter;

	center.x = ((((int)ray->v_hit.pos.x + ray->v_xshift) >> BLOCK_SIZE_BIT)
			<< BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
	center.y = (((int)ray->v_hit.pos.y >> BLOCK_SIZE_BIT)
			<< BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
	set_sprite_widthline(&line, &center, v);
	if (get_line_intersection(line, dlinenew(v->player.pos, dvectoradd(
						ray->v_hit.pos, ray->v_step)), &inter))
	{
		ray->v_hit.offset = (int)dist(line.p1, inter);
		ray->v_hit.distance = playerdist_fisheyeless(inter, ray->angle, v);
		ray->v_hit.height = BLOCK_SIZE / ray->v_hit.distance * v->project_dist;
		return (1);
	}
	return (0);
}

char		search_v_sprite_hit(t_ray *ray, t_vars const *v)
{
	ray->v_hit.distance = 999999999999999;
	ray->v_hit.pos.x -= ray->v_step.x;
	ray->v_hit.pos.y -= ray->v_step.y;
	while (((ray->orientation[1] == EAST && ray->v_hit.pos.x > v->player.pos.x)
				|| (ray->orientation[1] == WEST && ray->v_hit.pos.x
					< v->player.pos.x)) && !is_in_map(v, ray->v_hit.pos.x
					+ ray->v_xshift, ray->v_hit.pos.y))
	{
		ray->v_hit.pos.x -= ray->v_step.x;
		ray->v_hit.pos.y -= ray->v_step.y;
	}
	while (!((ray->orientation[1] == EAST && ray->v_hit.pos.x < v->player.pos.x)
				|| (ray->orientation[1] == WEST && ray->v_hit.pos.x
					> v->player.pos.x) || !is_in_map(v, ray->v_hit.pos.x
						+ ray->v_xshift, ray->v_hit.pos.y)))
	{
		if (is_sprite(v, ray->v_hit.pos.x + ray->v_xshift, ray->v_hit.pos.y)
				&& check_in_v_sprite_width(ray, v))
			return (1);
		ray->v_hit.pos.x -= ray->v_step.x;
		ray->v_hit.pos.y -= ray->v_step.y;
	}
	return (0);
}
