/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:16:44 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/02 15:16:44 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	deg_to_rad(double angle)
{
	return (angle * (M_PI / 180));
}

double	rad_to_deg(double angle)
{
	return ((180 * angle) / M_PI);
}

double	fix_angle(double angle)
{
	if (angle < 0)
		return (angle + 2 * M_PI);
	else if (angle >= 2 * M_PI)
		return (angle - 2 * M_PI);
	else
		return (angle);
}
