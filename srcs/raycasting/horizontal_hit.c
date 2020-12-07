/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_dist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:38:58 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/05 13:38:58 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

static void	get_hfirst_intercept(t_vars const *v, t_hit *intercept,
		t_orientation const *orientation, double const angle)
{
	intercept->y = ((int)v->player.y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
	if (orientation[0] == SOUTH)
		intercept->y += BLOCK_SIZE;
	intercept->x = v->player.x + (v->player.y - intercept->y)
		/ tan(angle);
}

static void	get_hstep(t_dvector *step, t_orientation const *orientation,
		double const angle)
{
	step->y = BLOCK_SIZE;
	if (orientation[0] == NORTH)
		step->y = -BLOCK_SIZE;
	step->x = BLOCK_SIZE / tan(angle);
	if ((orientation[1] == WEST && step->x > 0)
			|| (orientation[1] == EAST && step->x < 0))
		step->x *= -1;
}

void		search_horiz_hit(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle)
{
	t_dvector	step;
	char		yshift;

	yshift = 0;
	if (orientation[0] == NORTH)
		yshift = -1;
	get_hfirst_intercept(v, intercept, orientation, angle);
	if (!is_in_map(v, intercept->x, intercept->y + yshift))
	{
		intercept->distance = 999999999999999;
		return ;
	}
	if (is_wall(v, intercept->x, intercept->y + yshift))
		return (set_ray_distance(v, intercept, angle));
	get_hstep(&step, orientation, angle);
	intercept->x += step.x;
	intercept->y += step.y;
	while (is_in_map(v, intercept->x, intercept->y + yshift))
	{
		if (is_wall(v, intercept->x, intercept->y + yshift))
			return (set_ray_distance(v, intercept, angle));
		intercept->x += step.x;
		intercept->y += step.y;
	}
	intercept->distance = 999999999999999;
}
