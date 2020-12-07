/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 14:08:49 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/05 14:08:49 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		is_in_map(t_vars *v, int x, int y)
{
	x >>= BLOCK_SIZE_BIT;
	y >>= BLOCK_SIZE_BIT;
	if (x < 0 || y < 0 || y >= v->map.max.y || x >= v->map.max.x)
		return (0);
	return (1);
}

int		is_wall(t_vars *v, int x, int y)
{
	if (v->map.grid[y >> BLOCK_SIZE_BIT][x >> BLOCK_SIZE_BIT] == '1')
		return (1);
	return (0);
}

int		is_sprite(t_vars *v, int x, int y)
{
	if (v->map.grid[y >> BLOCK_SIZE_BIT][x >> BLOCK_SIZE_BIT] == 'S')
		return (1);
	return (0);
}
