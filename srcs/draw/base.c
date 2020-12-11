/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:54:08 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:54:08 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void		mlx_img_pixel_put(t_vars const *v, unsigned const x,
		unsigned const y, unsigned const color)
{
	char	*dst;

	if (x >= v->res.x || y >= v->res.y)
		return ;
	dst = v->img.addr + (y * v->img.line_length)
		+ (x * (v->img.bits_per_pixel / 8));
	*(unsigned *)dst = color;
}

unsigned	mlx_img_pixel_get_value(t_img_data img_data, int x, int y)
{
	char	*dst;

	dst = img_data.addr + (y * img_data.line_length)
		+ (x * (img_data.bits_per_pixel / 8));
	return (*(unsigned *)dst);
}

void		mlx_clear_img(t_vars *v, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			mlx_img_pixel_put(v, j, i, BLACK);
			j++;
		}
		i++;
	}
}
