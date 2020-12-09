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

void		search_horiz_sprite(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle)
{
	t_dvector	step;
	/* t_hit	bp; */
	char		yshift;

	/* bp = *intercept; */
	yshift = 0;
	if (orientation[0] == NORTH)
		yshift = -1;
	intercept->distance = 999999999999999;
	get_hstep(&step, orientation, angle);
	while (((orientation[0] == NORTH && intercept->y < v->player.y)
				|| (orientation[0] == SOUTH && intercept->y > v->player.y))
			&& !is_in_map(v, intercept->x, intercept->y + yshift))
	{
		intercept->x -= step.x;
		intercept->y -= step.y;
	}
	if ((orientation[0] == NORTH && intercept->y > v->player.y)
			|| (orientation[0] == SOUTH && intercept->y < v->player.y)
			|| !is_in_map(v, intercept->x, intercept->y + yshift))
		return ;
	if (is_sprite(v, intercept->x, intercept->y + yshift))
	{
		t_dvector center;
		t_dvector t[2];
		center.x = (((int)intercept->x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
		center.y = ((((int)intercept->y + yshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
		t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * 32;
		t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * 32;
		t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * 32;
		t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * 32;
		if (get_line_intersection(t[0].x, t[0].y, t[1].x, t[1].y, v->player.x, v->player.y, intercept->x + step.x, intercept->y + step.y, &intercept->x, &intercept->y))
		{
			intercept->offset = (int)dist(t[0], intercept->x, intercept->y);
			/* intercept->x = center.x; */
			/* intercept->y = center.y; */
			return (set_sprite_distance(v, intercept, angle));
		}
		return ;
	}
	intercept->x -= step.x;
	intercept->y -= step.y;
	while (!((orientation[0] == NORTH && intercept->y > v->player.y)
				|| (orientation[0] == SOUTH && intercept->y < v->player.y)
				|| !is_in_map(v, intercept->x, intercept->y + yshift)))
	{
		if (is_sprite(v, intercept->x, intercept->y + yshift))
		{
			t_dvector center;
			t_dvector t[2];
			center.x = (((int)intercept->x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			center.y = ((((int)intercept->y + yshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * 32;
			t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * 32;
			t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * 32;
			t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * 32;
			if (get_line_intersection(t[0].x, t[0].y, t[1].x, t[1].y, v->player.x, v->player.y, intercept->x + step.x, intercept->y + step.y, &intercept->x, &intercept->y))
			{
				intercept->offset = (int)dist(t[0], intercept->x, intercept->y);
				/* intercept->x = center.x; */
				/* intercept->y = center.y; */
				return (set_sprite_distance(v, intercept, angle));
			}
			return ;
		}
		intercept->x -= step.x;
		intercept->y -= step.y;
	}
}
