/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:46:31 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/29 12:30:07 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>

# include "debug.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# include "libft.h"
# include "get_next_line.h"
# include "structs.h"
# include "free.h"
# include "errors.h"

int		ft_atoitrim(char const **nptr);

void	parse_scene(char const * const file, t_vars *v);


#endif
