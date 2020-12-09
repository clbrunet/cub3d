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

void	get_angle_orientation(t_orientation *orientation, double const angle)
{
	if (angle < M_PI)
		orientation[0] = NORTH;
	else
		orientation[0] = SOUTH;
	if (M_PI_2 < angle && angle < 3 * M_PI_2)
		orientation[1] = WEST;
	else
		orientation[1] = EAST;
}

void	set_ray_distance(t_vars *v, t_hit *intercept, double const angle)
{
	intercept->distance = sqrt((v->player.x - intercept->x)
			* (v->player.x - intercept->x)
			+ (v->player.y - intercept->y) * (v->player.y - intercept->y));
	intercept->distance *= cos(fabs(v->player.angle - angle));
}

void	set_sprite_distance(t_vars *v, t_hit *intercept, double const angle)
{
	intercept->distance = sqrt((v->player.x - intercept->x)
			* (v->player.x - intercept->x)
			+ (v->player.y - intercept->y) * (v->player.y - intercept->y));
	intercept->distance *= cos(fabs(v->player.angle - angle));
	/* (void)angle; */
}

void	cast_ray(t_vars *v, int col, double const angle)
{
	t_orientation	orientation[2];
	t_hit			horiz_hit;
	t_hit			vert_hit;

	get_angle_orientation(orientation, angle);
	search_horiz_hit(&horiz_hit, v, orientation, angle);
	search_vert_hit(&vert_hit, v, orientation, angle);
	if (horiz_hit.distance < vert_hit.distance)
	{
		horiz_hit.height = BLOCK_SIZE / horiz_hit.distance * v->project_dist;
		horiz_hit.offset = (int)horiz_hit.x % BLOCK_SIZE;
		if (orientation[0] == SOUTH)
		{
			horiz_hit.offset = abs(horiz_hit.offset - (BLOCK_SIZE - 1));
			draw_col(col, &horiz_hit, &v->textures.south, v);
		}
		else
			draw_col(col, &horiz_hit, &v->textures.north, v);
		search_vert_sprite(&vert_hit, v, orientation, angle);
		vert_hit.height = BLOCK_SIZE / vert_hit.distance * v->project_dist;
		if (vert_hit.distance < horiz_hit.distance)
			draw_col(col, &vert_hit, &v->textures.sprite, v);
		search_horiz_sprite(&horiz_hit, v, orientation, angle);
		horiz_hit.height = BLOCK_SIZE / horiz_hit.distance * v->project_dist;
		if (horiz_hit.distance < 999999999999)
			draw_col(col, &horiz_hit, &v->textures.sprite, v);
	}
	else
	{
		vert_hit.height = BLOCK_SIZE / vert_hit.distance * v->project_dist;
		vert_hit.offset = (int)vert_hit.y % BLOCK_SIZE;
		if (orientation[1] == WEST)
		{
			vert_hit.offset = abs(vert_hit.offset - (BLOCK_SIZE - 1));
			draw_col(col, &vert_hit, &v->textures.west, v);
		}
		else
			draw_col(col, &vert_hit, &v->textures.east, v);
		search_horiz_sprite(&horiz_hit, v, orientation, angle);
		horiz_hit.height = BLOCK_SIZE / horiz_hit.distance * v->project_dist;
		if (horiz_hit.distance < vert_hit.distance)
			draw_col(col, &horiz_hit, &v->textures.sprite, v);
		search_vert_sprite(&vert_hit, v, orientation, angle);
		vert_hit.height = BLOCK_SIZE / vert_hit.distance * v->project_dist;
		if (vert_hit.distance < 999999999999)
			draw_col(col, &vert_hit, &v->textures.sprite, v);
	}
}

void	cast_rays(t_vars *v)
{
	int			col;
	double		angle;

	angle = normalize_angle(v->player.angle + v->player.fov / 2);
	col = 0;
	while (col < v->res.x)
	{
		cast_ray(v, col, angle);
		angle = normalize_angle(angle - v->player.fov / v->res.x);
		col++;
	}
}
