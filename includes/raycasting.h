/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:16:47 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/01 18:16:47 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "debug.h"

# include <math.h>
# include <stdlib.h>

# include "libft.h"
# include "utils.h"
# include "structs.h"
# include "defines.h"

# define BLACK	0x00000000
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF

typedef enum	e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				t_orientation;

void	get_angle_orientation(t_orientation *orientation, double const angle);
void	set_ray_distance(t_vars *v, t_hit *intercept, double const angle);

void		search_horiz_hit(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle);
void		search_vert_hit(t_hit *intercept, t_vars *v,
		t_orientation const *orientation, double const angle);

void			cast_rays(t_vars *v);

#endif
