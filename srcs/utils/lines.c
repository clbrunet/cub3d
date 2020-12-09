/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 06:30:52 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/09 06:30:52 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>
#include <math.h>

t_dvector	dvectornew(double x, double y)
{
	t_dvector	new;

	new.x = x;
	new.y = y;
	return (new);
}

char get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y, 
    double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y)
{
    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    double s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return (1);
    }

    return (0);
}

double	dist(t_dvector p0, double p1x, double p1y)
{
	return (sqrt((p0.x - p1x) * (p0.x - p1x)
			+ (p0.y - p1y) * (p0.y - p1y)));
}

/* char get_line_intersection(t_dvector p0, t_dvector p1, */
/*     double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y) */
/* { */
/*     double s1_x, s1_y, s2_x, s2_y; */
/*     s1_x = p1.x - p0.x;     s1_y = p1.y - p0.y; */
/*     s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y; */

/*     double s, t; */
/*     s = (-s1_y * (p0.x - p2_x) + s1_x * (p0.y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y); */
/*     t = ( s2_x * (p0.y - p2_y) - s2_y * (p0.x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y); */

/*     if (s >= 0 && s <= 1 && t >= 0 && t <= 1) */
/*     { */
/*         if (i_x != NULL) */
/*             *i_x = p0.x + (t * s1_x); */
/*         if (i_y != NULL) */
/*             *i_y = p0.y + (t * s1_y); */
/*         return (1); */
/*     } */

/*     return (0); */
/* } */
