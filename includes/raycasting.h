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

void	get_angle_orientation(t_ray *ray);
void	set_ray_distance(t_hit *hit, double const angle, t_vars *v);

void	search_h_wall_hit(t_ray *ray, t_vars *v);
char	search_h_sprite_hit(t_ray *ray, t_vars *v);
void	search_v_wall_hit(t_ray *ray, t_vars *v);
char	search_v_sprite_hit(t_ray *ray, t_vars *v);

void	cast_rays(t_vars *v);

#endif
