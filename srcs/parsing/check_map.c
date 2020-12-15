/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:15:10 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 09:48:33 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_player_props(t_vars *v, char c, int y, int x)
{
	v->player.fov = M_PI / 3;
	v->player.height = v->res.y / 2;
	v->player.speed = (double)(v->res.x * v->res.y) / 96000;
	v->player.pos.x = (double)BLOCK_SIZE / 2 + BLOCK_SIZE * x;
	v->player.pos.y = (double)BLOCK_SIZE / 2 + BLOCK_SIZE * y;
	v->player.health = 5;
	if (c == 'N')
		v->player.angle = M_PI_2;
	else if (c == 'S')
		v->player.angle = 3 * M_PI_2;
	else if (c == 'W')
		v->player.angle = M_PI;
	else
		v->player.angle = 0;
}

void		check_map_chars(t_vars *v)
{
	int		i;
	int		j;
	char	count;

	count = 0;
	i = -1;
	while (v->map.grid[++i])
	{
		j = -1;
		while (v->map.grid[i][++j])
		{
			if (ft_strchr("NSWE", v->map.grid[i][j]))
			{
				set_player_props(v, v->map.grid[i][j], i, j);
				count++;
			}
			else if (!ft_strchr(" 012HM", v->map.grid[i][j]))
				error("Map contains wrong chars", v, ERROR, NULL);
		}
	}
	if (count == 0)
		error("Player missing", v, ERROR, NULL);
	else if (count > 1)
		error("Multiplayer is not yet available", v, ERROR, NULL);
}

void		check_map(t_vars *v, int y, int x)
{
	if (y - 1 < 0 || !v->map.grid[y + 1] || x - 1 < 0 || !v->map.grid[y][x + 1]
			|| v->map.grid[y + 1][x] == ' ' || v->map.grid[y - 1][x] == ' '
			|| v->map.grid[y][x + 1] == ' ' || v->map.grid[y][x - 1] == ' ')
		error("Map not properly closed", v, ERROR, NULL);
	if (v->map.grid[y][x] == 'H')
		v->map.grid[y][x] = 'h';
	else if (v->map.grid[y][x] == 'M')
		v->map.grid[y][x] = 'm';
	else if (v->map.grid[y][x] == '2')
		v->map.grid[y][x] = 'f';
	else
		v->map.grid[y][x] = 'e';
	if (v->map.grid[y + 1][x] == '0' || v->map.grid[y + 1][x] == 'H'
			|| v->map.grid[y + 1][x] == 'M' || v->map.grid[y + 1][x] == '2')
		check_map(v, y + 1, x);
	if (v->map.grid[y - 1][x] == '0' || v->map.grid[y - 1][x] == 'H'
			|| v->map.grid[y - 1][x] == 'M' || v->map.grid[y - 1][x] == '2')
		check_map(v, y - 1, x);
	if (v->map.grid[y][x + 1] == '0' || v->map.grid[y][x + 1] == 'H'
			|| v->map.grid[y][x + 1] == 'M' || v->map.grid[y][x + 1] == '2')
		check_map(v, y, x + 1);
	if (v->map.grid[y][x - 1] == '0' || v->map.grid[y][x - 1] == 'H'
			|| v->map.grid[y][x - 1] == 'M' || v->map.grid[y][x - 1] == '2')
		check_map(v, y, x - 1);
}
