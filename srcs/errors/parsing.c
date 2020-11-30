/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 10:59:09 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/30 10:59:09 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	parsing_error(char *error_msg, t_vars *v)
{
	free_config(&v->config);
	free_strs(v->map.grid);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_msg, 2);
	exit(1);
}

void	check_elems(t_vars *v)
{
	if (v->config.res.x == -1)
		parsing_error("Resolution missing.", v);
	else if (!v->config.textures.north)
		parsing_error("North texture missing.", v);
	else if (!v->config.textures.south)
		parsing_error("South texture missing.", v);
	else if (!v->config.textures.west)
		parsing_error("West texture missing.", v);
	else if (!v->config.textures.east)
		parsing_error("East texture missing.", v);
	else if (!v->config.textures.sprite)
		parsing_error("Sprite texture missing.", v);
	else if (v->config.floor_color.full == -1)
		parsing_error("Floor color missing.", v);
	else if (v->config.ceilling_color.full == -1)
		parsing_error("Ceilling color missing.", v);
}

void	check_map(t_vars *v, int y, int x)
{
	if (y - 1 < 0 || !v->map.grid[y + 1] || x - 1 < 0 || !v->map.grid[y][x + 1]
			|| v->map.grid[y + 1][x] == ' ' || v->map.grid[y - 1][x] == ' '
			|| v->map.grid[y][x + 1] == ' ' || v->map.grid[y][x - 1] == ' ')
		parsing_error("Map not properly closed.", v);
	if (v->map.grid[y][x] == '2')
		v->map.grid[y][x] = 'S';
	else
		v->map.grid[y][x] = 'E';
	if (v->map.grid[y + 1][x] == '0' || v->map.grid[y + 1][x] == '2')
		check_map(v, y + 1, x);
	if (v->map.grid[y - 1][x] == '0' || v->map.grid[y - 1][x] == '2')
		check_map(v, y - 1, x);
	if (v->map.grid[y][x + 1] == '0' || v->map.grid[y][x + 1] == '2')
		check_map(v, y, x + 1);
	if (v->map.grid[y][x - 1] == '0' || v->map.grid[y][x - 1] == '2')
		check_map(v, y, x - 1);
}
