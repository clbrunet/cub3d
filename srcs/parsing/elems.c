/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 07:13:15 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 15:21:39 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"

static void	parse_res(char const *line, t_vars *v)
{
	int		screen_width;
	int		screen_heigth;

	ft_trimspaces(&line);
	if (v->res.x != 0 || v->res.y != 0)
		error("Multiple resolutions infos", v, ERROR);
	v->res.x = ft_atoitrim(&line);
	ft_trimspaces(&line);
	v->res.y = ft_atoitrim(&line);
	ft_trimspaces(&line);
	if (*line || v->res.x == 0 || v->res.y == 0)
		error("Wrong resolution infos", v, ERROR);
	mlx_get_screen_size(v->mlx, &screen_width, &screen_heigth);
	if (v->res.x > (unsigned)screen_width)
		v->res.x = screen_width;
	if (v->res.y > (unsigned)screen_heigth)
		v->res.y = screen_heigth;
}

static void	parse_texture(char const *line, t_texture *texture, t_vars *v)
{
	if (texture->width)
		error("Multiple textures infos", v, ERROR);
	ft_trimspaces(&line);
	if (!*line)
		error("Wrong textures infos", v, ERROR);
	else if (!(texture->img.img = mlx_xpm_file_to_image(v->mlx, (char *)line,
			&texture->width, &texture->height)))
		error("Texture xpm file to image failed", v, ERROR);
	texture->img.addr = mlx_get_data_addr(texture->img.img,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
}

static void	parse_color(char const *line, t_color *color_ptr, t_vars *v)
{
	ft_trimspaces(&line);
	color_ptr->bytes[3] = 0;
	if (!ft_isdigit(*line))
		error("Wrong colors infos", v, ERROR);
	color_ptr->bytes[2] = ft_atoitrim(&line);
	if (*line == ',')
		line++;
	else
		error("Wrong colors infos", v, ERROR);
	if (!ft_isdigit(*line))
		error("Wrong colors infos", v, ERROR);
	color_ptr->bytes[1] = ft_atoitrim(&line);
	if (*line == ',')
		line++;
	else
		error("Wrong colors infos", v, ERROR);
	if (!ft_isdigit(*line))
		error("Wrong colors infos", v, ERROR);
	color_ptr->bytes[0] = ft_atoitrim(&line);
	ft_trimspaces(&line);
	if (*line)
		error("Wrong colors infos", v, ERROR);
}

static void	parse_elem(char const *line, t_vars *v)
{
	if (line[0] == 'R' && (line[1] == ' ' || !line[1]))
		parse_res(line + 1, v);
	else if (line[0] == 'N' && line[1] == 'O' && (line[2] == ' ' || !line[2]))
		parse_texture(line + 2, &v->textures.north, v);
	else if (line[0] == 'S' && line[1] == 'O' && (line[2] == ' ' || !line[2]))
		parse_texture(line + 2, &v->textures.south, v);
	else if (line[0] == 'W' && line[1] == 'E' && (line[2] == ' ' || !line[2]))
		parse_texture(line + 2, &v->textures.west, v);
	else if (line[0] == 'E' && line[1] == 'A' && (line[2] == ' ' || !line[2]))
		parse_texture(line + 2, &v->textures.east, v);
	else if (line[0] == 'S' && (line[1] == ' ' || !line[1]))
		parse_texture(line + 1, &v->textures.sprite, v);
	else if (line[0] == 'F' && (line[1] == ' ' || !line[1]))
		parse_color(line + 1, &v->colors.floor, v);
	else if (line[0] == 'C' && (line[1] == ' ' || !line[1]))
		parse_color(line + 1, &v->colors.ceilling, v);
	else
		error("Wrong element", v, ERROR);
}

void		parse_elems(char const *const scene_path, int const fd, t_vars *v)
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
	if (ret == -1)
		error(scene_path, v, PERROR);
	else if (count != 8)
		error("Wrong number of elements", v, ERROR);
}
