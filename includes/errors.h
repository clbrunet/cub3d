/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:01:36 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/30 11:01:36 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "debug.h"

# include "libft.h"
# include "free.h"

void	parsing_error(char *error_msg, t_vars *v);
void	check_elems(t_vars *v);
void	check_map(t_vars *v, int y, int x);

#endif
