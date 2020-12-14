/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:54:08 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/12 18:30:48 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

t_color		fog(t_color color, double distance)
{
	double	fog_ratio;

	fog_ratio = distance / 400;
	if (fog_ratio > 0.4)
	{
		if (distance / 700 < 0.4)
			fog_ratio = 0.4;
		else
			fog_ratio = distance / 700;
		if (fog_ratio > 0.6 && distance / 1000 < 0.6)
			fog_ratio = 0.6;
		else if (fog_ratio > 0.6)
			fog_ratio = distance / 1000;
		if (fog_ratio > 0.80 && distance / 3000 < 0.80)
			fog_ratio = 0.80;
		else if (fog_ratio > 0.80)
			fog_ratio = distance / 3000;
		if (fog_ratio > 1)
			fog_ratio = 1;
	}
	color.bytes.red = color.bytes.red * (1 - fog_ratio) + 0 * fog_ratio;
	color.bytes.green = color.bytes.green * (1 - fog_ratio) + 60 * fog_ratio;
	color.bytes.blue = color.bytes.blue * (1 - fog_ratio) + 180 * fog_ratio;
	return (color);
}

void		mlx_img_pixel_put(t_vars const *v, unsigned const x,
		unsigned const y, t_color const color)
{
	char	*dst;

	if (x >= v->res.x || y >= v->res.y)
		return ;
	dst = v->img.addr + (y * v->img.line_length) + (x * 4);
	*(unsigned *)dst = color.full;
}

void		bmp_data_pixel_put(t_vars const *v, unsigned const x,
		unsigned const y, t_color const color)
{
	v->first_image_colors[y][x].bgr.blue = color.bytes.blue;
	v->first_image_colors[y][x].bgr.green = color.bytes.green;
	v->first_image_colors[y][x].bgr.red = color.bytes.red;
}

unsigned	mlx_img_pixel_get_value(t_img_data const *img_data, int x, int y)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length) + (x * 4);
	return (*(unsigned *)dst);
}

void		mlx_clear_img(t_vars *v, int x, int y)
{
	int		i;
	int		j;
	t_color black;

	black.full = BLACK;
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			mlx_img_pixel_put(v, j, i, black);
			j++;
		}
		i++;
	}
}
