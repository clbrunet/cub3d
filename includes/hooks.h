/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:39:38 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:44:00 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdlib.h>
# include <math.h>

# include "mlx.h"
# include "defines.h"
# include "data_structures.h"
# include "utils.h"

void	one_axis_movements(t_vars *v);
char	two_axis_movements(t_vars *v);

int		keypress_hook(int keycode, t_vars *v);
int		keyrelease_hook(int keycode, t_vars *v);
int		loop_hook(t_vars *v);

#endif
