/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:37:36 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 14:37:36 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	get_sprite_data(unsigned *texture_col, t_texture *texture,
		t_hit const *hit, t_vars const *v)
{
	if (hit->map_char == 'h')
		*texture = v->textures.regeneration;
	else
		*texture = v->textures.monster;
	*texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width);
}

double	get_floor_data(int y, t_ray const *ray, t_dvector *inter,
		t_vars const *v)
{
	double	dist;

	dist = (double)(BLOCK_SIZE_2 * v->project_dist)
		/ (double)(y - (double)v->res.y / 2)
		/ cos(fabs(v->player.angle - ray->angle));
	inter->x = v->player.pos.x + cos(ray->angle) * dist;
	if (inter->x < 0)
		inter->x = 0;
	inter->y = v->player.pos.y - sin(ray->angle) * dist;
	if (inter->y < 0)
		inter->y = 0;
	return (dist);
}

double	get_ceilling_data(int y, t_ray const *ray, t_dvector *inter,
		t_vars const *v)
{
	double	dist;

	dist = (BLOCK_SIZE_2 * v->project_dist
			/ (double)((double)v->res.y / 2 - y))
		/ cos(fabs(v->player.angle - ray->angle));
	inter->x = v->player.pos.x + cos(ray->angle) * dist;
	if (inter->x < 0)
		inter->x = 0;
	inter->y = v->player.pos.y - sin(ray->angle) * dist;
	if (inter->y < 0)
		inter->y = 0;
	return (dist);
}
