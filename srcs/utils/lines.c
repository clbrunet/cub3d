/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 06:30:52 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/13 13:24:48 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_dvector	dvectoradd(t_dvector v1, t_dvector v2)
{
	t_dvector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	return (res);
}

t_dline		dlinenew(t_dvector p1, t_dvector p2)
{
	t_dline	new;

	new.p1 = p1;
	new.p2 = p2;
	return (new);
}

double		dist(t_dvector p1, t_dvector p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x)
				+ (p1.y - p2.y) * (p1.y - p2.y)));
}

double		playerdist_fisheyeless(t_dvector p, double const angle,
		t_vars const *v)
{
	return (sqrt(pow(v->player.pos.x - p.x, 2) + pow((v->player.pos.y
						- p.y), 2)) * cos(fabs(v->player.angle - angle)));
}

char		get_line_intersection(t_dline l1, t_dline l2, t_dvector *inter)
{
	t_dvector	s1;
	t_dvector	s2;
	double		s;
	double		t;

	s1.x = l1.p2.x - l1.p1.x;
	s1.y = l1.p2.y - l1.p1.y;
	s2.x = l2.p2.x - l2.p1.x;
	s2.y = l2.p2.y - l2.p1.y;
	s = (-s1.y * (l1.p1.x - l2.p1.x) + s1.x * (l1.p1.y - l2.p1.y))
		/ (-s2.x * s1.y + s1.x * s2.y);
	t = (s2.x * (l1.p1.y - l2.p1.y) - s2.y * (l1.p1.x - l2.p1.x))
		/ (-s2.x * s1.y + s1.x * s2.y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		inter->x = l1.p1.x + (t * s1.x);
		inter->y = l1.p1.y + (t * s1.y);
		return (1);
	}
	return (0);
}
