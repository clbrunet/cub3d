/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:50:17 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 13:50:17 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_res(void *to_free, char const *line, t_vars *v)
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

void	parse_texture(void *to_free, char const *line, t_texture *texture,
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
