/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:18:14 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/02 15:18:14 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "defines.h"
#include "structs.h"

double		deg_to_rad(double angle);
double		rad_to_deg(double angle);
double		normalize_angle(double angle);

int			ft_atoitrim(char const **nptr);

int			is_in_map(t_vars *v, int x, int y);
int			is_wall(t_vars *v, int x, int y);
int			is_sprite(t_vars *v, int x, int y);

t_dvector	dvectornew(double x, double y);
char get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y, 
    double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y);
double	dist(t_dvector p0, double p1x, double p1y);

#endif
