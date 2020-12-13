/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 07:18:20 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/06 12:04:20 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"

static void		strsadd_back(char ***strs_ptr, unsigned len, char *new,
		t_vars *v)
{
	char		**tmp;
	unsigned	j;

	if (!(tmp = malloc(sizeof(char *) * (len + 1))))
	{
		free(new);
		error("Malloc failed", v, ERROR, NULL);
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

static size_t	get_max_strlen(char const **strs)
{
	size_t		len;
	size_t		max;

	max = 0;
	while (*strs)
	{
		len = ft_strlen(*strs);
		if (len > max)
			max = len;
		strs++;
	}
	return (max);
}

static void		addspaces(t_vars *v, char const ***strs_ptr)
{
	size_t		len;
	size_t		max;
	char		*tmp;
	unsigned	i;

	max = get_max_strlen(*strs_ptr);
	i = 0;
	while ((*strs_ptr)[i])
	{
		len = ft_strlen((*strs_ptr)[i]);
		if (len < max)
		{
			if (!(tmp = malloc(sizeof(char) * (max + 1))))
				error("Malloc failed", v, ERROR, NULL);
			ft_strcpy(tmp, (*strs_ptr)[i]);
			free((void *)(*strs_ptr)[i]);
			while (len < max)
				tmp[len++] = ' ';
			tmp[len] = '\0';
			(*strs_ptr)[i] = tmp;
		}
		i++;
	}
}

static void		set_map_props(t_map *map)
{
	map->minimap_factor = 0.2;
	map->max.x = ft_strlen(map->grid[0]);
	map->max.y = ft_strslen((const char **)map->grid);
}

void			parse_map(char const *const scene_path, int const fd,
		t_map *map, t_vars *v)
{
	int			ret;
	char		*line;
	unsigned	i;

	i = 0;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if (!*line)
		{
			free(line);
			if (!ret)
				break ;
			else if (i == 0)
				continue ;
			else
				error("Map empty line, or too many elements", v, ERROR, NULL);
		}
		strsadd_back(&map->grid, ++i, line, v);
	}
	if (ret == -1)
		error(scene_path, v, PERROR, NULL);
	else if (ret == -2)
		error("Malloc failed", v, ERROR, NULL);
	addspaces(v, (char const ***)&map->grid);
	set_map_props(map);
}
