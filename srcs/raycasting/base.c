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

double	get_ray_distance(t_vars *v, t_dvector const *intercept,
		double const angle)
{
	double	distorted;
	double	angle_shift;

	distorted = sqrt((v->player.x - intercept->x) *(v->player.x - intercept->x)
			+ (v->player.y - intercept->y) * (v->player.y - intercept->y));
	angle_shift = fabs(v->player.angle - angle);
	return (distorted * cos(angle_shift));
}

int		get_project_height(double height, t_vars *v)
{
	return (BLOCK_SIZE / height * v->project_dist);
}

void	cast_ray(t_vars *v, int col, double const angle)
{
	t_orientation	orientation[2];
	double			hwall_dist;
	double			vwall_dist;

	get_angle_orientation(orientation, angle);
	hwall_dist = get_hwall_dist(v, orientation, angle);
	vwall_dist = get_vwall_dist(v, orientation, angle);
	if (hwall_dist < vwall_dist)
	{
		if (orientation[0] == NORTH)
			draw_col(col, get_project_height(hwall_dist, v), RED, v);
		else
			draw_col(col, get_project_height(hwall_dist, v), 0x00FFFF00, v);
	}
	else
	{
		if (orientation[1] == WEST)
			draw_col(col, get_project_height(vwall_dist, v), GREEN, v);
		else
			draw_col(col, get_project_height(vwall_dist, v), BLUE, v);
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
