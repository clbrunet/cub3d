/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 07:13:15 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/13 11:17:10 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"

static void	parse_elem2(char const *line, t_vars *v)
{
	if (line[0] == 'w' && line[1] == '0' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.weapon[0], v);
	else if (line[0] == 'w' && line[1] == '1' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.weapon[1], v);
	else if (line[0] == 'w' && line[1] == '2' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.weapon[2], v);
	else if (line[0] == 'w' && line[1] == '3' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.weapon[3], v);
	else if (line[0] == 'w' && line[1] == '4' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.weapon[4], v);
	else if (line[0] == 'w' && line[1] == '5' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.weapon[5], v);
	else
		error("Wrong element, or missing element", v, ERROR, (void *)line);
}

static void	parse_elem(char const *line, t_vars *v)
{
	if (line[0] == 'R' && (line[1] == ' ' || !line[1]))
		parse_res((void *)line, line + 1, v);
	else if (line[0] == 'N' && line[1] == 'O' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.north, v);
	else if (line[0] == 'S' && line[1] == 'O' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.south, v);
	else if (line[0] == 'W' && line[1] == 'E' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.west, v);
	else if (line[0] == 'E' && line[1] == 'A' && (line[2] == ' ' || !line[2]))
		parse_texture((void *)line, line + 2, &v->textures.east, v);
	else if (line[0] == 'M' && (line[1] == ' ' || !line[1]))
		parse_texture((void *)line, line + 1, &v->textures.monster, v);
	else if (line[0] == 'H' && (line[1] == ' ' || !line[1]))
		parse_texture((void *)line, line + 1, &v->textures.regeneration, v);
	else if (line[0] == 'h' && (line[1] == ' ' || !line[1]))
		parse_texture((void *)line, line + 1, &v->textures.health, v);
	else if (line[0] == 'F' && (line[1] == ' ' || !line[1]))
		parse_texture((void *)line, line + 1, &v->textures.floor, v);
	else if (line[0] == 'C' && (line[1] == ' ' || !line[1]))
		parse_texture((void *)line, line + 1, &v->textures.ceilling, v);
	else if (line[0] == 'S' && (line[1] == ' ' || !line[1]))
		parse_color((void *)line, line + 1, &v->fog, v);
	else
		parse_elem2(line, v);
}

void		parse_elems(char const *const scene_path, int const fd, t_vars *v)
{
	int		ret;
	char	*line;
	int		count;

	count = 0;
	while (count < 17 && (ret = get_next_line(fd, &line)) >= 0)
	{
		if (*line)
		{
			parse_elem(line, v);
			count++;
		}
		free(line);
		if (!ret)
			break ;
	}
	if (ret == -1)
		error(scene_path, v, PERROR, NULL);
	else if (ret == -2)
		error("Malloc failed", v, ERROR, NULL);
	else if (count != 17)
		error("Wrong number of elements", v, ERROR, NULL);
}
