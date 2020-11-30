/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:09:29 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/28 18:25:23 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char **av)
{
	t_vars	v;

	if (ac < 2 || ac > 3) // wrong nb of args
		return (1);
	else if (ac == 2)
	{
		initialize_config(&v.config);
		v.map.grid = NULL;
		parse_scene(av[1], &v);
		print_config(&v.config);
		print_map(v.map.grid);
		printf_player(&v.player);
		free_config(&v.config);
		free_strs(v.map.grid);

	}
	else
	{
		// --save
	}
	return (0);
}