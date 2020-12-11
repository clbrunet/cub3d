/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:38:58 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 12:16:42 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "minilibx.h"

static void	set_h_first_hit_and_step(t_ray *ray, t_vars const *v)
{
	ray->h_hit.pos.y = ((int)v->player.pos.y >> BLOCK_SIZE_BIT)
		<< BLOCK_SIZE_BIT;
	if (ray->orientation[0] == SOUTH)
		ray->h_hit.pos.y += BLOCK_SIZE;
	ray->h_hit.pos.x = v->player.pos.x + (v->player.pos.y - ray->h_hit.pos.y)
		/ tan(ray->angle);
	ray->h_step.y = BLOCK_SIZE;
	if (ray->orientation[0] == NORTH)
		ray->h_step.y = -BLOCK_SIZE;
	ray->h_step.x = BLOCK_SIZE / tan(ray->angle);
	if ((ray->orientation[1] == WEST && ray->h_step.x > 0)
			|| (ray->orientation[1] == EAST && ray->h_step.x < 0))
		ray->h_step.x *= -1;
}

void		search_h_wall_hit(t_ray *ray, t_vars const *v)
{
	ray->h_hit.distance = 999999999999999;
	if (ray->orientation[0] == NORTH)
		ray->h_yshift = -1;
	else
		ray->h_yshift = 0;
	set_h_first_hit_and_step(ray, v);
	if (!is_in_map(v, ray->h_hit.pos.x, ray->h_hit.pos.y + ray->h_yshift))
		return ;
	else if (is_wall(v, ray->h_hit.pos.x, ray->h_hit.pos.y + ray->h_yshift))
	{
		ray->h_hit.distance = playerdist_fisheyeless(ray->h_hit.pos,
				ray->angle, v);
		return ;
	}
	ray->h_hit.pos = dvectoradd(ray->h_hit.pos, ray->h_step);
	while (is_in_map(v, ray->h_hit.pos.x, ray->h_hit.pos.y + ray->h_yshift))
	{
		if (is_wall(v, ray->h_hit.pos.x, ray->h_hit.pos.y + ray->h_yshift))
		{
			ray->h_hit.distance = playerdist_fisheyeless(ray->h_hit.pos,
					ray->angle, v);
			return ;
		}
		ray->h_hit.pos = dvectoradd(ray->h_hit.pos, ray->h_step);
	}
}

void		display_h_wall(t_ray *ray, t_vars const *v)
{
	ray->wall_dist = ray->h_hit.distance;
	ray->h_hit.height = BLOCK_SIZE / ray->h_hit.distance * v->project_dist;
	ray->h_hit.offset = (int)ray->h_hit.pos.x % BLOCK_SIZE;
	if (ray->orientation[0] == SOUTH)
	{
		ray->h_hit.offset = abs((int)ray->h_hit.offset - (BLOCK_SIZE - 1));
		draw_col(ray->col, &ray->h_hit, &v->textures.south, v);
	}
	else
		draw_col(ray->col, &ray->h_hit, &v->textures.north, v);
}

static char	check_in_h_sprite_width(t_ray *ray, t_vars const *v)
{
	t_dvector	center;
	t_dline		line;
	t_dvector	inter;

	center.x = (((int)ray->h_hit.pos.x >> BLOCK_SIZE_BIT)
			<< BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
	center.y = ((((int)ray->h_hit.pos.y + ray->h_yshift) >> BLOCK_SIZE_BIT)
			<< BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
	set_sprite_widthline(&line, &center, v);
	if (get_line_intersection(line, dlinenew(v->player.pos, dvectoradd(
						ray->h_hit.pos, ray->h_step)), &inter))
	{
		ray->h_hit.offset = (int)dist(line.p1, inter);
		ray->h_hit.distance = playerdist_fisheyeless(inter, ray->angle, v);
		ray->h_hit.height = BLOCK_SIZE / ray->h_hit.distance * v->project_dist;
		return (1);
	}
	return (0);
}

char		search_h_sprite_hit(t_ray *ray, t_vars const *v)
{
	ray->h_hit.distance = 999999999999999;
	ray->h_hit.pos.x -= ray->h_step.x;
	ray->h_hit.pos.y -= ray->h_step.y;
	while (((ray->orientation[0] == NORTH && ray->h_hit.pos.y < v->player.pos.y)
				|| (ray->orientation[0] == SOUTH && ray->h_hit.pos.y
					> v->player.pos.y)) && !is_in_map(v, ray->h_hit.pos.x,
					ray->h_hit.pos.y + ray->h_yshift))
	{
		ray->h_hit.pos.x -= ray->h_step.x;
		ray->h_hit.pos.y -= ray->h_step.y;
	}
	while (!((ray->orientation[0] == NORTH && ray->h_hit.pos.y
					> v->player.pos.y) || (ray->orientation[0] == SOUTH
						&& ray->h_hit.pos.y < v->player.pos.y)
				|| !is_in_map(v, ray->h_hit.pos.x,
						ray->h_hit.pos.y + ray->h_yshift)))
	{
		if (is_sprite(v, ray->h_hit.pos.x, ray->h_hit.pos.y + ray->h_yshift)
				&& check_in_h_sprite_width(ray, v))
			return (1);
		ray->h_hit.pos.x -= ray->h_step.x;
		ray->h_hit.pos.y -= ray->h_step.y;
	}
	return (0);
}
