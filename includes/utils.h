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

double	deg_to_rad(double angle);
double	rad_to_deg(double angle);
double	normalize_angle(double angle);

int		ft_atoitrim(char const **nptr);

int		is_in_map(t_vars *v, int x, int y);
int		is_wall(t_vars *v, int x, int y);
int		is_sprite(t_vars *v, int x, int y);

#endif
