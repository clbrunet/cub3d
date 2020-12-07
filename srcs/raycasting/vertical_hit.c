/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:40:27 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/05 13:40:27 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	get_vfirst_intercept(t_vars const *v, t_hit *intercept,
		t_orientation const *orientation, double const angle)
{
	intercept->x = ((int)v->player.x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
	if (orientation[1] == EAST)
		intercept->x += BLOCK_SIZE;
	intercept->y = v->player.y + (v->player.x - intercept->x) * tan(angle);
}

static void	get_vstep(t_dvector *step, t_orientation const *orientation,
		double const angle)
{
	step->x = BLOCK_SIZE;
	if (orientation[1] == WEST)
		step->x *= -1;
	step->y = BLOCK_SIZE * tan(angle);
	if ((orientation[0] == NORTH && step->y > 0)
			|| (orientation[0] == SOUTH && step->y < 0))
		step->y *= -1;
}

void		search_vert_hit(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle)
{
	t_dvector	step;
	char		xshift;

	xshift = 0;
	if (orientation[1] == WEST)
		xshift = -1;
	get_vfirst_intercept(v, intercept, orientation, angle);
	if (!is_in_map(v, intercept->x + xshift, intercept->y))
	{
		intercept->distance = 999999999999999;
		return ;
	}
	else if (is_wall(v, intercept->x + xshift, intercept->y))
		return (set_ray_distance(v, intercept, angle));
	get_vstep(&step, orientation, angle);
	intercept->x += step.x;
	intercept->y += step.y;
	while (is_in_map(v, intercept->x + xshift, intercept->y))
	{
		if (is_wall(v, intercept->x + xshift, intercept->y))
			return (set_ray_distance(v, intercept, angle));
		intercept->x += step.x;
		intercept->y += step.y;
	}
	intercept->distance = 999999999999999;
}
