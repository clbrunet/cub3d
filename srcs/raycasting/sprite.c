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
int colu;

void	draw_sprite(t_hit *hit, t_vars *v, int col)
{
	int		y;
	/* int		texture_col; */
	/* texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width); */
	if (hit->height > v->res.y)
	{
		y = 0;
		while (y < v->res.y)
		{
			mlx_img_pixel_put(v->img, col, y, BLACK);
			y++;
		}
		return ;
	}
	y = 0;
	while (y < hit->height)
	{
		mlx_img_pixel_put(v->img, col, y + (v->res.y / 2 - hit->height / 2),
				BLACK);
		y++;
	}
}
void	set_sprite_distancet(t_vars *v, t_hit *intercept, double const angle)
{
	intercept->distance = sqrt((v->player.x - intercept->x)
			* (v->player.x - intercept->x)
			+ (v->player.y - intercept->y) * (v->player.y - intercept->y));
	/* intercept->distance *= cos(fabs(v->player.angle - angle)); */
	(void)angle;
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

void		search_horiz_spritet(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle)
{
	t_dvector	step;
	/* t_hit	bp; */
	char		yshift;

	/* bp = *intercept; */
	yshift = 0;
	if (orientation[0] == SOUTH)
		yshift = -1;
	intercept->distance = 999999999999999;
	if ((orientation[0] == NORTH && intercept->y > v->player.y)
			|| (orientation[0] == SOUTH && intercept->y < v->player.y)
			|| !is_in_map(v, intercept->x, intercept->y + yshift))
		return ;
	if (is_sprite(v, intercept->x, intercept->y + yshift))
	{
		t_dvector center;
		/* t_dvector t[2]; */
		center.x = (((int)intercept->x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
		center.y = ((((int)intercept->y + yshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
		/* t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * 32; */
		/* t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * 32; */
		/* t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * 32; */
		/* t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * 32; */
		/* int dist = round(sqrt((t[0].x - t[1].x) * (t[0].x - t[1].x) */
		/* 			+ (t[0].y - t[1].y) * (t[0].y - t[1].y))); */
		intercept->x = center.x;
		intercept->y = center.y;
		return (set_sprite_distancet(v, intercept, angle));
	}
	get_hstep(&step, orientation, angle);
	step.x = -step.x;
	step.y = -step.y;
	intercept->x += step.x;
	intercept->y += step.y;
	while (!((orientation[0] == NORTH && intercept->y > v->player.y)
				|| (orientation[0] == SOUTH && intercept->y < v->player.y)
				|| !is_in_map(v, intercept->x, intercept->y + yshift)))
	{
		if (is_sprite(v, intercept->x, intercept->y + yshift))
		{
			t_dvector center;
			/* t_dvector t[2]; */
			center.x = (((int)intercept->x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			center.y = ((((int)intercept->y + yshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			/* t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * 32; */
			/* t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * 32; */
			/* t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * 32; */
			/* t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * 32; */
			/* int dist = round(sqrt((t[0].x - t[1].x) * (t[0].x - t[1].x) */
			/* 			+ (t[0].y - t[1].y) * (t[0].y - t[1].y))); */
			intercept->x = center.x;
			intercept->y = center.y;
			return (set_sprite_distancet(v, intercept, angle));
		}
		intercept->x += step.x;
		intercept->y += step.y;
	}
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

void		search_vert_spritet(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle)
{
	t_dvector	step;
	char		xshift;

	xshift = 0;
	if (orientation[1] == EAST)
		xshift = -1;
	intercept->distance = 999999999999999;
	if ((orientation[1] == EAST && intercept->x < v->player.x)
			|| (orientation[1] == WEST && intercept->x > v->player.x)
			|| !is_in_map(v, intercept->x + xshift, intercept->y))
		return ;
	if (is_sprite(v, intercept->x + xshift, intercept->y))
	{
		t_dvector center;
		/* t_dvector t[2]; */
		center.x = ((((int)intercept->x + xshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
		center.y = (((int)intercept->y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
		/* t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * 32; */
		/* t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * 32; */
		/* t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * 32; */
		/* t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * 32; */
		/* int dist = round(sqrt((t[0].x - t[1].x) * (t[0].x - t[1].x) */
		/* 			+ (t[0].y - t[1].y) * (t[0].y - t[1].y))); */
		intercept->x = center.x;
		intercept->y = center.y;
		return (set_sprite_distancet(v, intercept, angle));
	}
	get_vstep(&step, orientation, angle);
	step.x = -step.x;
	step.y = -step.y;
	intercept->x += step.x;
	intercept->y += step.y;
	while (!((orientation[1] == EAST && intercept->x < v->player.x)
			|| (orientation[1] == WEST && intercept->x > v->player.x)
			|| !is_in_map(v, intercept->x + xshift, intercept->y)))
	{
		if (is_sprite(v, intercept->x + xshift, intercept->y))
		{
			t_dvector center;
			/* t_dvector t[2]; */
			center.x = ((((int)intercept->x + xshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			center.y = (((int)intercept->y >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT) + BLOCK_SIZE_2;
			/* t[0].x = center.x + cos(normalize_angle(v->player.angle + M_PI_2)) * 32; */
			/* t[0].y = center.y - sin(normalize_angle(v->player.angle + M_PI_2)) * 32; */
			/* t[1].x = center.x + cos(normalize_angle(v->player.angle - M_PI_2)) * 32; */
			/* t[1].y = center.y - sin(normalize_angle(v->player.angle - M_PI_2)) * 32; */
			/* int dist = round(sqrt((t[0].x - t[1].x) * (t[0].x - t[1].x) */
			/* 			+ (t[0].y - t[1].y) * (t[0].y - t[1].y))); */
			intercept->x = center.x;
			intercept->y = center.y;
			return (set_sprite_distancet(v, intercept, angle));
		}
		intercept->x += step.x;
		intercept->y += step.y;
	}
}

void	cast_ray_sprite(t_vars *v, int col, double const angle)
{
	t_orientation	orientation[2];
	t_hit			vert;
	t_hit			horiz;
	/* t_hit			sprite; */

	colu = col;
	get_angle_orientation(orientation, angle);
	search_horiz_hit(&horiz, v, orientation, angle);
	if (horiz.distance < 999999999999)
	{
		search_horiz_spritet(&horiz, v, orientation, angle);
		horiz.height = BLOCK_SIZE / horiz.distance * v->project_dist;
		if (horiz.distance < 999999999999)
			draw_sprite(&horiz, v, col);
	}
	search_vert_hit(&vert, v, orientation, angle);
	/* if (sprite.distance * cos(fabs(v->player.angle - angle)) < horiz.distance */
	/* 		&& sprite.distance * cos(fabs(v->player.angle - angle)) < vwall.distance) */
	if (vert.distance < 999999999999)
	{
		search_vert_spritet(&vert, v, orientation, angle);
		vert.height = BLOCK_SIZE / vert.distance * v->project_dist;
		if (vert.distance < 999999999999)
			draw_sprite(&vert, v, col);
	}
	/* if (sprite.distance * cos(fabs(v->player.angle - angle)) < horiz.distance */
	/* 		&& sprite.distance * cos(fabs(v->player.angle - angle)) < vwall.distance) */
	/* 	draw_sprite(&sprite, v, col); */
}

/* void	search_sprite(t_hit *intercept, t_vars *v, */
/* 		t_orientation const *orientation, double const angle) */
/* { */
/* 	t_hit hh; */
/* 	t_hit vv; */
/* 	t_dvector hs; */
/* 	t_dvector vs; */

/* 	char		xshift; */

/* 	xshift = 0; */
/* 	if (orientation[1] == WEST) */
/* 		xshift = -1; */
/* 	char		yshift; */

/* 	yshift = 0; */
/* 	if (orientation[0] == NORTH) */
/* 		yshift = -1; */
/* 	get_hfirst_intercept(v, &hh, orientation, angle); */
/* 	get_vfirst_intercept(v, &vv, orientation, angle); */
/* 	intercept->distance = 999999999999999; */
/* 	get_vstep(&hs, orientation, angle); */
/* 	get_hstep(&vs, orientation, angle); */
/* 	/1* if (!is_in_map(v, hh.x, hh.y + yshift)&&is_wall(v, hh.x, hh.y + yshift)) *1/ */
/* 	/1* 	return ; *1/ */
/* 	/1* if (is_wall(v, vv.x + xshift, vv.y)) *1/ */
/* 	/1* 	return ; *1/ */
/* 	if (is_in_map(v, hh.x, hh.y + yshift) && is_sprite(v, hh.x, hh.y + yshift) */
/* 			&&is_in_map(v, hh.x +hs.x, hh.y +hs.y - yshift)&& is_sprite(v, hh.x + hs.x, hh.y + hs.y - yshift)) */
/* 	{ */
/* 		intercept->x = (hh.x + (hh.x + hs.x)) / 2; */
/* 		intercept->y = (hh.y + (hh.y + hs.y)) / 2; */
/* 		hh.y = (((int)hh.y + yshift) >> BLOCK_SIZE_BIT) */
/* 			<< BLOCK_SIZE_BIT; */
/* 		hh.y += BLOCK_SIZE_2; */
/* 		hh.x = ((int)hh.x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT; */
/* 		hh.x += BLOCK_SIZE_2; */
/* 		intercept->distance = sqrt((hh.x - intercept->x) */
/* 				* (hh.x - intercept->x) */
/* 				+ (hh.y - intercept->y) * (hh.y - intercept->y)); */
/* 		if (intercept->distance <= 32) */
/* 		{ */
/* 			intercept->x = hh.x; */
/* 			intercept->y = hh.y; */
/* 			return (set_ray_distance(v, intercept, angle)); */
/* 		} */
/* 		return ; */
/* 	} */
/* 	else if (is_in_map(v, vv.x + xshift, vv.y) &&is_sprite(v, vv.x + xshift, vv.y) */
/* 			&& is_in_map(v, vv.x + vs.x - xshift, vv.y + vs.y) && is_sprite(v, vv.x + vs.x - xshift, vv.y + vs.y)) */
/* 	{ */
/* 		intercept->x = (vv.x + (vv.x + vs.x)) / 2; */
/* 		intercept->y = (vv.y + (vv.y + vs.y)) / 2; */
/* 		vv.y = ((int)vv.y >> BLOCK_SIZE_BIT) */
/* 			<< BLOCK_SIZE_BIT; */
/* 		vv.y += BLOCK_SIZE_2; */
/* 		vv.x = (((int)vv.x + xshift) >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT; */
/* 		vv.x += BLOCK_SIZE_2; */
/* 		intercept->distance = sqrt((vv.x - intercept->x) */
/* 				* (vv.x - intercept->x) */
/* 				+ (vv.y - intercept->y) * (vv.y - intercept->y)); */
/* 		if (intercept->distance <= 32) */
/* 		{ */
/* 			intercept->x = vv.x; */
/* 			intercept->y = vv.y; */
/* 			return (set_ray_distance(v, intercept, angle)); */
/* 		} */
/* 		return ; */
/* 	} */
/* 	else if (is_in_map(v, hh.x, hh.y + yshift)&&is_sprite(v, hh.x, hh.y + yshift) */
/* 			&& is_in_map(v, vv.x - xshift, vv.y) &&is_sprite(v, vv.x - xshift, vv.y)) */
/* 	{ */
/* 		intercept->x = (hh.x + vv.x) / 2; */
/* 		intercept->y = (hh.y + vv.y) / 2; */
/* 		hh.y = (((int)hh.y + yshift) >> BLOCK_SIZE_BIT) */
/* 			<< BLOCK_SIZE_BIT; */
/* 		hh.y += BLOCK_SIZE_2; */
/* 		hh.x = ((int)hh.x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT; */
/* 		hh.x += BLOCK_SIZE_2; */
/* 		intercept->distance = sqrt((hh.x - intercept->x) */
/* 				* (hh.x - intercept->x) */
/* 				+ (hh.y - intercept->y) * (hh.y - intercept->y)); */
/* 		if (intercept->distance <= 32) */
/* 		{ */
/* 			intercept->x = hh.x; */
/* 			intercept->y = hh.y; */
/* 			return (set_ray_distance(v, intercept, angle)); */
/* 		} */
/* 		return ; */
/* 	} */
/* 	else if (is_in_map(v, vv.x + xshift, vv.y)&&is_sprite(v, vv.x + xshift, vv.y) */
/* 			&& is_in_map(v, hh.x, hh.y - yshift)&&is_sprite(v, hh.x, hh.y - yshift)) */
/* 	{ */
/* 		intercept->x = (hh.x + vv.x) / 2; */
/* 		intercept->y = (hh.y + vv.y) / 2; */
/* 		hh.y = (((int)hh.y + yshift) >> BLOCK_SIZE_BIT) */
/* 			<< BLOCK_SIZE_BIT; */
/* 		hh.y += BLOCK_SIZE_2; */
/* 		hh.x = ((int)hh.x >> BLOCK_SIZE_BIT) << BLOCK_SIZE_BIT; */
/* 		hh.x += BLOCK_SIZE_2; */
/* 		intercept->distance = sqrt((hh.x - intercept->x) */
/* 				* (hh.x - intercept->x) */
/* 				+ (hh.y - intercept->y) * (hh.y - intercept->y)); */
/* 		if (intercept->distance <= 32) */
/* 		{ */
/* 			intercept->x = hh.x; */
/* 			intercept->y = hh.y; */
/* 			return (set_ray_distance(v, intercept, angle)); */
/* 		} */
/* 	} */
/* } */
