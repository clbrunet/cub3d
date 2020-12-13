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

unsigned	mlx_img_pixel_get_value(t_img_data img_data, int x, int y)
{
	char	*dst;

	dst = img_data.addr + (y * img_data.line_length) + (x * 4);
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
