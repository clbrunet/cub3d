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

static void	parse_res(void *to_free, char const *line, t_vars *v)
{
	int		screen_width;
	int		screen_heigth;

	ft_trimspaces(&line);
	if (v->res.x != 0 || v->res.y != 0)
		error("Multiple resolutions infos", v, ERROR, to_free);
	v->res.x = ft_atoitrim(&line);
	ft_trimspaces(&line);
	v->res.y = ft_atoitrim(&line);
	ft_trimspaces(&line);
	if (*line || v->res.x == 0 || v->res.y == 0)
		error("Wrong resolution infos", v, ERROR, to_free);
	mlx_get_screen_size(v->mlx, &screen_width, &screen_heigth);
	if (v->res.x > (unsigned)screen_width)
		v->res.x = screen_width;
	if (v->res.y > (unsigned)screen_heigth)
		v->res.y = screen_heigth;
}

static void	parse_texture(void *to_free, char const *line, t_texture *texture,
		t_vars *v)
{
	if (texture->width)
		error("Multiple textures infos", v, ERROR, to_free);
	ft_trimspaces(&line);
	if (!*line)
		error("Wrong textures infos", v, ERROR, to_free);
	else if (!(texture->img.img = mlx_xpm_file_to_image(v->mlx, (char *)line,
			&texture->width, &texture->height)))
		error("Texture xpm file to image failed", v, ERROR, to_free);
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
}

void	parse_color(void *to_free, char const *line, t_color *color_ptr,
		t_vars *v)
{
	ft_trimspaces(&line);
	color_ptr->bytes.alpha = 0;
	if (!ft_isdigit(*line))
		error("Wrong colors infos", v, ERROR, to_free);
	color_ptr->bytes.red = ft_atoitrim(&line);
	if (*line == ',')
		line++;
	else
		error("Wrong colors infos", v, ERROR, to_free);
	if (!ft_isdigit(*line))
		error("Wrong colors infos", v, ERROR, to_free);
	color_ptr->bytes.green = ft_atoitrim(&line);
	if (*line == ',')
		line++;
	else
		error("Wrong colors infos", v, ERROR, to_free);
	if (!ft_isdigit(*line))
		error("Wrong colors infos", v, ERROR, to_free);
	color_ptr->bytes.blue = ft_atoitrim(&line);
	ft_trimspaces(&line);
	if (*line)
		error("Wrong colors infos", v, ERROR, to_free);
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
	else
		error("Wrong element, or missing element", v, ERROR, (void *)line);
}

void		parse_elems(char const *const scene_path, int const fd, t_vars *v)
{
	int		ret;
	char	*line;
	int		count;

	count = 0;
	while (count < 10 && (ret = get_next_line(fd, &line)) >= 0)
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
	else if (count != 10)
		error("Wrong number of elements", v, ERROR, NULL);
}
