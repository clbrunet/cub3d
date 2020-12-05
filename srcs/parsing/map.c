/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 07:18:20 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/05 10:28:56 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"

static void	strsadd_back(char ***strs_ptr, unsigned len, char *new, t_vars *v)
{
	char		**tmp;
	unsigned	j;

	if (!(tmp = malloc(sizeof(char *) * (len + 1))))
	{
		free(new);
		error("Malloc failed", v, ERROR);
	}
	j = 0;
	while (j < len - 1)
	{
		tmp[j] = (*strs_ptr)[j];
		j++;
	}
	tmp[j++] = new;
	tmp[j] = NULL;
	free(*strs_ptr);
	*strs_ptr = tmp;
}

static void	addspaces(t_vars *v, char ***strs_ptr)
{
	size_t		len;
	size_t		max;
	char		*tmp;
	unsigned	i;

	max = 0;
	i = 0;
	while ((*strs_ptr)[i])
	{
		len = ft_strlen((*strs_ptr)[i]);
		if (len > max)
			max = len;
		i++;
	}
	i = 0;
	while ((*strs_ptr)[i])
	{
		len = ft_strlen((*strs_ptr)[i]);
		if (len < max)
		{
			if (!(tmp = malloc(sizeof(char) * (max + 1))))
				error("Malloc failed", v, ERROR);
			ft_strcpy(tmp, (*strs_ptr)[i]);
			free((*strs_ptr)[i]);
			while (len < max)
				tmp[len++] = ' ';
			tmp[len] = '\0';
			(*strs_ptr)[i] = tmp;
		}
		i++;
	}
}

static void	set_map_props(t_map *map)
{
	map->minimap_factor = 0.2;
	map->max.x = ft_strlen(map->grid[0]);
	map->max.y = ft_strslen((const char **)map->grid);
}

void	parse_map(char const *const scene_path, int const fd, t_map *map,
		t_vars *v)
{
	int			ret;
	char		*line;
	unsigned	i;

	i = 1;
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (!*line)
		{
			free(line);
			if (!ret)
				break ;
			else if (i == 1)
				continue ;
			else
				error("Empty line in map", v, ERROR);
		}
		strsadd_back(&map->grid, i, line, v);
		i++;
	}
	if (ret == -1)
		error(scene_path, v, PERROR);
	addspaces(v, &map->grid);
	set_map_props(map);
}
