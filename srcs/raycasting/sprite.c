/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 11:15:07 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/07 11:36:53 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "minilibx.h"

void	draw_sprite(t_hit *hit, t_vars *v, int col)
{
	int		y;
	int		x;
	/* int		texture_col; */

	/* texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width); */
	if (hit->height > v->res.y)
	{
		y = 0;
		while (y < v->res.y)
		{
			x = col;
			while (x < hit->height + col && x < v->res.x)
				mlx_img_pixel_put(v->img, x++, y, BLACK);
			y++;
		}
		return ;
	}
	y = 0;
	while (y < hit->height)
	{
		x = 0;
		while (x < hit->height && x + col < v->res.x)
		{
			mlx_img_pixel_put(v->img, x + col, y + (v->res.y / 2 - hit->height / 2),
					BLACK);
			x++;
		}
		y++;
	}
}

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

void		search_horiz_sprite(t_hit *intercept, t_vars *v,
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
	if (is_sprite(v, intercept->x, intercept->y + yshift))
	{
		intercept->y = (((int)intercept->y + yshift) >> BLOCK_SIZE_BIT)
			<< BLOCK_SIZE_BIT;
		/* if (orientation[0] == SOUTH) */
		/* 	intercept->y += BLOCK_SIZE; */
		intercept->y += BLOCK_SIZE_2;
		intercept->x = ((int)intercept->x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
		intercept->x += BLOCK_SIZE_2;
		/* if (orientation[0] == ) */
		/* 	intercept->x += BLOCK_SIZE; */
		return (set_ray_distance(v, intercept, angle));
	}
	get_hstep(&step, orientation, angle);
	intercept->x += step.x;
	intercept->y += step.y;
	while (is_in_map(v, intercept->x, intercept->y + yshift))
	{
		if (is_sprite(v, intercept->x, intercept->y + yshift))
		{
			intercept->y = (((int)intercept->y + yshift) >> BLOCK_SIZE_BIT)
				<< BLOCK_SIZE_BIT;
			/* if (orientation[0] == SOUTH) */
			/* 	intercept->y += BLOCK_SIZE; */
			intercept->y += BLOCK_SIZE_2;
			intercept->x = ((int)intercept->x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
			intercept->x += BLOCK_SIZE_2;
			/* if (orientation[0] == ) */
			/* 	intercept->x += BLOCK_SIZE; */
			return (set_ray_distance(v, intercept, angle));
		}
		intercept->x += step.x;
		intercept->y += step.y;
	}
	intercept->distance = 999999999999999;
}

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

void		search_vert_sprite(t_hit *intercept, t_vars *v,
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
	else if (is_sprite(v, intercept->x + xshift, intercept->y))
	{
		intercept->y = ((int)intercept->y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
		intercept->y += BLOCK_SIZE_2;
		intercept->x = (((int)intercept->x + xshift) >> BLOCK_SIZE_BIT)
			<< BLOCK_SIZE_BIT;
		intercept->x += BLOCK_SIZE_2;
		return (set_ray_distance(v, intercept, angle));
	}
	get_vstep(&step, orientation, angle);
	intercept->x += step.x;
	intercept->y += step.y;
	while (is_in_map(v, intercept->x + xshift, intercept->y))
	{
		if (is_sprite(v, intercept->x + xshift, intercept->y))
		{
			intercept->y = ((int)intercept->y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT;
			intercept->y += BLOCK_SIZE_2;
			intercept->x = (((int)intercept->x + xshift) >> BLOCK_SIZE_BIT)
				<< BLOCK_SIZE_BIT;
			intercept->x += BLOCK_SIZE_2;
			return (set_ray_distance(v, intercept, angle));
		}
		intercept->x += step.x;
		intercept->y += step.y;
	}
	intercept->distance = 999999999999999;
}

void	cast_ray_sprite(t_vars *v, int col, double const angle)
{
	t_orientation	orientation[2];
	t_hit			horiz_hit;
	t_hit			vert_hit;
	static t_ivector ve = {0};
	static t_ivector h = {0};

	if (col == 0)
	{
		ve.x = 0;
		ve.y = 0;
		h.x = 0;
		h.y = 0;
	}
	get_angle_orientation(orientation, angle);
	search_horiz_sprite(&horiz_hit, v, orientation, angle);
	horiz_hit.height = BLOCK_SIZE / horiz_hit.distance * v->project_dist;
	search_vert_sprite(&vert_hit, v, orientation, angle);
	vert_hit.height = BLOCK_SIZE / vert_hit.distance * v->project_dist;
	if (horiz_hit.distance < 1000
			&& !(ve.x == (int)horiz_hit.x >> BLOCK_SIZE_BIT
				&& ve.y == ((int)horiz_hit.y - 1) >> BLOCK_SIZE_BIT)
			&& !(h.x == (int)horiz_hit.x >> BLOCK_SIZE_BIT
				&& h.y == ((int)horiz_hit.y - 1) >> BLOCK_SIZE_BIT))
	{
		h.x = (int)horiz_hit.x >> BLOCK_SIZE_BIT;
		h.y = ((int)horiz_hit.y - 1) >> BLOCK_SIZE_BIT;
		draw_sprite(&horiz_hit, v, col);
	}
	else if (vert_hit.distance < 1000
			&& !(ve.x == (int)vert_hit.x >> BLOCK_SIZE_BIT
				&& ve.y == ((int)vert_hit.y - 1) >> BLOCK_SIZE_BIT)
			&& !(h.x == (int)vert_hit.x >> BLOCK_SIZE_BIT
				&& h.y == ((int)vert_hit.y - 1) >> BLOCK_SIZE_BIT))
	{
		ve.x = (int)vert_hit.x >> BLOCK_SIZE_BIT;
		ve.y = ((int)vert_hit.y - 1) >> BLOCK_SIZE_BIT;
		draw_sprite(&vert_hit, v, col);
	}
}
