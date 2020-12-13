/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:18:14 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:36:20 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "defines.h"
# include "data_structures.h"

void		free_strs(char **strs);

double		deg_to_rad(double angle);
double		rad_to_deg(double angle);
double		fix_angle(double angle);

int			ft_atoitrim(char const **nptr);

char		is_in_map(t_vars const *v, int x, int y);
char		is_wall(t_vars const *v, unsigned x, unsigned y);
char		is_sprite(t_vars const *v, unsigned x, unsigned y);

t_dvector	dvectoradd(t_dvector v1, t_dvector v2);
t_dline		dlinenew(t_dvector p1, t_dvector p2);
double		dist(t_dvector p1, t_dvector p2);
double		playerdist_fisheyeless(t_dvector p, double const angle,
		t_vars const *v);
char		get_line_intersection(t_dline l1, t_dline l2,
		t_dvector *inter);

#endif
