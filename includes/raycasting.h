/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:16:47 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 16:58:33 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "debug.h"

# include <math.h>
# include <stdlib.h>

# include "libft.h"
# include "utils.h"
# include "data_structures.h"
# include "defines.h"

void	set_sprite_widthline(t_dline *line, t_dvector *center,
		t_vars const *v);

void	search_h_wall_hit(t_ray *ray, t_vars const *v);
void	display_h_wall(t_ray *ray, t_vars const *v);
char	search_h_sprite_hit(t_ray *ray, t_vars const *v);

void	search_v_wall_hit(t_ray *ray, t_vars const *v);
void	display_v_wall(t_ray *ray, t_vars const *v);
char	search_v_sprite_hit(t_ray *ray, t_vars const *v);

void	cast_rays(t_vars const *v);

#endif
