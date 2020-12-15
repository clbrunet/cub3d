/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:46:31 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:36:32 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"
# include "utils.h"
# include "data_structures.h"
# include "defines.h"

void	error(char const *const error_msg, t_vars *v, t_error const error,
		void *to_free);

void	parse_res(void *to_free, char const *line, t_vars *v);
void	parse_texture(void *to_free, char const *line, t_texture *texture,
		t_vars *v);
void	parse_color(void *to_free, char const *line, t_color *color_ptr,
		t_vars *v);

void	parse_elems(char const *const scene_path, int const fd, t_vars *v);
void	check_elems(t_vars *v);

void	parse_map(char const *const scene_path, int const fd,
		t_map *map, t_vars *v);
void	check_map(t_vars *v, int y, int x);
void	check_map_chars(t_vars *v);

void	check_av(char const *scene_path, char const *save_flag, t_vars *v);
void	parse_scene(char const *const scene_path, t_vars *v);

#endif
