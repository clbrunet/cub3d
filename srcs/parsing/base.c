/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:39:15 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 12:12:53 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_av(char const *scene_path, char const *save_flag, t_vars *v)
{
	unsigned	len;

	len = ft_strlen(scene_path);
	if (len < 4)
		error("Wrong scene file extension", v, ERROR);
	scene_path += len - 4;
	if (!ft_strnstr(scene_path, ".cub", 4))
		error("Wrong scene file extension", v, ERROR);
	if (save_flag && (ft_strlen(save_flag) != 6
				|| !ft_strnstr(save_flag, "--save", 6)))
		error("Second parameter must be \"--save\"", v, ERROR);
}

void	initialize_parsing(t_vars *v)
{
	v->res.x = 0;
	v->res.y = 0;
	v->textures.north.width = 0;
	v->textures.south.width = 0;
	v->textures.west.width = 0;
	v->textures.east.width = 0;
	v->textures.sprite.width = 0;
	v->colors.ceilling.full = (unsigned)-1;
	v->colors.floor.full = (unsigned)-1;
	v->map.grid = NULL;
}

void	parse_scene(char const *const scene_path, t_vars *v)
{
	int		fd;

	if ((fd = open(scene_path, O_RDONLY)) == -1)
		error(scene_path, v, PERROR);
	parse_elems(scene_path, fd, v);
	check_elems(v);
	parse_map(scene_path, fd, &v->map, v);
	check_map_chars(v);
	check_map(v, (int)v->player.pos.y >> BLOCK_SIZE_BIT,
			(int)v->player.pos.x >> BLOCK_SIZE_BIT);
	v->project_dist = ((double)v->res.x / 2) / tan(v->player.fov / 2);
}
