/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:13:02 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/06 12:09:23 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void	mlx_img_pixel_put(t_img_data img_data, int x, int y, unsigned color)
{
	char	*dst;

	dst = img_data.addr + (y * img_data.line_length)
		+ (x * (img_data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned	mlx_img_pixel_get_value(t_img_data img_data, int x, int y)
{
	char	*dst;

	dst = img_data.addr + (y * img_data.line_length)
		+ (x * (img_data.bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	mlx_clear_img(t_img_data img_data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			mlx_img_pixel_put(img_data, j, i, RED);
			j++;
		}
		i++;
	}
}

void	draw_rect(t_vars *v, int tlx, int tly, int brx, int bry, int color)
{
	int		bp;

	bp = tlx;
	while (tly <= bry)
	{
		tlx = bp;
		while (tlx <= brx)
			mlx_img_pixel_put(v->img, tlx++, tly, color);
		tly++;
	}
}

void	draw_minimap(t_vars *v)
{
	int		i;
	int		j;

	i = 0;
	while (i < v->map.max.y * BLOCK_SIZE * v->map.minimap_factor)
	{
		j = 0;
		while (j < v->map.max.x * BLOCK_SIZE * v->map.minimap_factor)
		{
			if (v->map.grid
					[(int)((double)i / v->map.minimap_factor) >> BLOCK_SIZE_BIT]
					[(int)(j / v->map.minimap_factor) >> BLOCK_SIZE_BIT] == '1')
				mlx_img_pixel_put(v->img, j, i, WHITE);
			else
				mlx_img_pixel_put(v->img, j, i, 0x00ffb74d);

			j++;
		}
		i++;
	}
	draw_rect(v, v->player.x * v->map.minimap_factor - 2,
			v->player.y * v->map.minimap_factor - 2,
			v->player.x * v->map.minimap_factor + 2,
			v->player.y * v->map.minimap_factor + 2, GREEN);
	double newx = v->player.x + cos(v->player.angle) * 10;
	double newy = v->player.y - sin(v->player.angle) * 10;
	draw_rect(v, newx * v->map.minimap_factor - 1,
			newy * v->map.minimap_factor - 1,
			newx * v->map.minimap_factor + 1,
			newy * v->map.minimap_factor + 1, GREEN);
	newx = newx + cos(v->player.angle) * 10;
	newy = newy - sin(v->player.angle) * 10;
	draw_rect(v, newx * v->map.minimap_factor - 1,
			newy * v->map.minimap_factor - 1,
			newx * v->map.minimap_factor + 1,
			newy * v->map.minimap_factor + 1, GREEN);
	newx = newx + cos(v->player.angle) * 10;
	newy = newy - sin(v->player.angle) * 10;
	draw_rect(v, newx * v->map.minimap_factor - 1,
			newy * v->map.minimap_factor - 1,
			newx * v->map.minimap_factor + 1,
			newy * v->map.minimap_factor + 1, GREEN);
	newx = newx + cos(v->player.angle) * 10;
	newy = newy - sin(v->player.angle) * 10;
	draw_rect(v, newx * v->map.minimap_factor - 1,
			newy * v->map.minimap_factor - 1,
			newx * v->map.minimap_factor + 1,
			newy * v->map.minimap_factor + 1, GREEN);
}

void	draw_col(int col, t_hit *hit, t_texture *texture, t_vars *v)
{
	int		y;
	int		texture_col;

	texture_col = (double)hit->offset / ((double)BLOCK_SIZE / texture->width);
	if (hit->height > v->res.y)
	{
		y = 0;
		while (y < v->res.y)
		{
			mlx_img_pixel_put(v->img, col, y,
					mlx_img_pixel_get_value(texture->img, texture_col,
						(y + (hit->height - v->res.y) / 2)
						* texture->height / hit->height));
			y++;
		}
		return ;
	}
	y = 0;
	while (y < v->res.y / 2 - hit->height / 2)
	{
		mlx_img_pixel_put(v->img, col, y, 0x0090caf9);
		y++;
	}
	y = 0;
	while (y < hit->height)
	{
		unsigned color = mlx_img_pixel_get_value(texture->img, texture_col,
				y * texture->height / hit->height);
		mlx_img_pixel_put(v->img, col, y + (v->res.y / 2 - hit->height / 2),
				color);
		y++;
	}
	while (y + (v->res.y / 2 - hit->height / 2) < v->res.y)
	{
		mlx_img_pixel_put(v->img, col, y + (v->res.y / 2 - hit->height / 2),
				0x00ffb74d);
		y++;
	}
}

