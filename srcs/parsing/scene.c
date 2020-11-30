/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:39:15 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/30 17:09:59 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "errors.h"
#include "parsing.h"

static void parse_res(char const *line, t_vars *v)
{
	ft_trimspaces(&line);
	if (/*!*line || */v->config.res.x != -1 || v->config.res.y != -1)
		parsing_error("Multiple resolutions infos.", v);
	v->config.res.x = ft_atoitrim(&line);
	ft_trimspaces(&line);
	v->config.res.y = ft_atoitrim(&line);
	ft_trimspaces(&line);
	if (*line || v->config.res.x == -1 || v->config.res.y == -1)
		parsing_error("Wrong resolution infos.", v);
}

static void parse_texture(char const *line, char **texture_ptr, t_vars *v)
{
	if (*texture_ptr)
		parsing_error("Multiple textures infos.", v);
	ft_trimspaces(&line);
	if (!*line)
		parsing_error("Wrong textures infos.", v);
	if (!(*texture_ptr = ft_strdup(line)))
		parsing_error("Malloc failed.", v);
}

static void parse_color(char const *line, t_color *color_ptr, t_vars *v)
{
	ft_trimspaces(&line);
	color_ptr->bytes[3] = 0;
	if (!ft_isdigit(*line))
		parsing_error("Wrong colors infos.", v);
	color_ptr->bytes[2] = ft_atoitrim(&line);
	if (*line == ',')
		line++;
	else
		parsing_error("Wrong colors infos.", v);
	if (!ft_isdigit(*line))
		parsing_error("Wrong colors infos.", v);
	color_ptr->bytes[1] = ft_atoitrim(&line);
	if (*line == ',')
		line++;
	else
		parsing_error("Wrong colors infos.", v);
	if (!ft_isdigit(*line))
		parsing_error("Wrong colors infos.", v);
	color_ptr->bytes[0] = ft_atoitrim(&line);
	ft_trimspaces(&line);
	if (*line)
		parsing_error("Wrong colors infos.", v);
}

static void	parse_elem(char const *line, t_vars *v)
{
	if (line[0] == 'R' && line[1] == ' ')
		parse_res(line + 1, v);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		parse_texture(line + 2, &v->config.textures.north, v);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		parse_texture(line + 2, &v->config.textures.south, v);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		parse_texture(line + 2, &v->config.textures.west, v);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		parse_texture(line + 2, &v->config.textures.east, v);
	else if (line[0] == 'S')
		parse_texture(line + 1, &v->config.textures.sprite, v);
	else if (line[0] == 'F')
		parse_color(line + 1, &v->config.floor_color, v);
	else if (line[0] == 'C')
		parse_color(line + 1, &v->config.ceilling_color, v);
	else
		parsing_error("Wrong element", v);
}

static void	parse_elems(int const fd, t_vars *v)
{
	int		ret;
	char	*line;
	int		count;

	count = 0;
	while (count < 8 && (ret = get_next_line(fd, &line)) != -1)
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
	if (count != 8)
		parsing_error("Wrong number of elements.", v);
}

static int	strsadd_back(char ***strs_ptr, unsigned len, char *new)
{
	char		**tmp;
	unsigned	j;

	if (!(tmp = malloc(sizeof(char *) * (len + 1))))
		return (0);
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
	return (1);
}

static void	parse_map(int const fd, t_map *map, t_vars *v)
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
				parsing_error("empty line in map.", v);
		}
		if (!strsadd_back(&map->grid, i, line))
		{
			free(line);
			parsing_error("malloc failed.", v);
		}
		i++;
	}
	/* set_map_props(map); */
}

static void	set_player_props(t_vars *v, char c, int y, int x)
{
	static char	count = 0;

	count++;
	if (count > 1)
		parsing_error("Multiplayer is not yet available.", v);
	v->player.fov = 60;
	v->player.height = 32;
	v->player.pos.x = x;
	v->player.pos.y = y;
	if (c == 'N')
		v->player.angle = 90;
	else if (c == 'S')
		v->player.angle = 270;
	else if (c == 'W')
		v->player.angle = 180;
	else
		v->player.angle = 0;
}

static void	search_player(t_vars *v)
{
	int		i;
	int		j;

	i = 0;
	while (v->map.grid[i])
	{
		j = 0;
		while (v->map.grid[i][j])
		{
			if (ft_strchr("NSWE", v->map.grid[i][j]))
				set_player_props(v, v->map.grid[i][j], i, j);
			else if (!ft_strchr(" 012", v->map.grid[i][j]))
				parsing_error("Map contains wrong chars.", v);
			j++;
		}
		i++;
	}
}

void	parse_scene(char const * const file, t_vars *v)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1) // TODO: print error
		exit(1);
	parse_elems(fd, v);
	check_elems(v);
	parse_map(fd, &v->map, v);
	search_player(v);
	check_map(v, v->player.pos.y, v->player.pos.x);
}
