/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:53:03 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:53:03 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "debug.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# include "mlx.h"
# include "defines.h"
# include "data_structures.h"

void		error(char const *const error_msg, t_vars *v, t_error const error);

void		mlx_img_pixel_put(t_vars const *v, unsigned const x,
		unsigned const y, t_color const color);
void		bmp_data_pixel_put(t_vars const *v, unsigned const x,
		unsigned const y, t_color const color);
unsigned	mlx_img_pixel_get_value(t_img_data img_data, int x, int y);

void		draw_col(unsigned const col, t_hit const *hit,
		t_texture const *texture, t_vars const *v);

int			write_bmp(t_vars const *v);

#endif
