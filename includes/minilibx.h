/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:15:34 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/05 11:06:38 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H
# define MINILIBX_H

# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "structs.h"
# include "enums.h"
# include "defines.h"

# define BLACK	0x00000000
# define WHITE	0x00FFFFFF
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF

void	error(char const *const error_msg, t_vars *v, t_error const error);
void	mlx_clear_img(t_img_data img_data, int x, int y);
void	draw_minimap(t_vars *v);
void	draw_col(int col, int height, int color, t_vars *v);

#endif
