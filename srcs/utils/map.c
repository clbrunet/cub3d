/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 14:08:49 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 15:18:53 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	is_in_map(t_vars const *v, int x, int y)
{
	x >>= BLOCK_SIZE_BIT;
	y >>= BLOCK_SIZE_BIT;
	if (x < 0 || y < 0
			|| (unsigned)y >= v->map.max.y || (unsigned)x >= v->map.max.x)
		return (0);
	return (1);
}

char	is_wall(t_vars const *v, unsigned x, unsigned y)
{
	x >>= BLOCK_SIZE_BIT;
	y >>= BLOCK_SIZE_BIT;
	if (v->map.grid[y][x] == '1' || v->map.grid[y][x] == 'f')
		return (1);
	return (0);
}

char	is_real_wall(t_vars const *v, unsigned x, unsigned y)
{
	if (v->map.grid[y >> BLOCK_SIZE_BIT][x >> BLOCK_SIZE_BIT] == '1')
		return (1);
	return (0);
}

char	is_sprite(t_vars const *v, unsigned x, unsigned y)
{
	x >>= BLOCK_SIZE_BIT;
	y >>= BLOCK_SIZE_BIT;
	if (v->map.grid[y][x] == 'h' || v->map.grid[y][x] == 'm')
		return (1);
	return (0);
}

char	is_monster(t_vars const *v, unsigned x, unsigned y)
{
	x >>= BLOCK_SIZE_BIT;
	y >>= BLOCK_SIZE_BIT;
	if (v->map.grid[y][x] == 'm')
		return (1);
	return (0);
}
