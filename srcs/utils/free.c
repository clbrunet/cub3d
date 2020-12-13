/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 06:38:37 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/11 17:38:16 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_strs(char **strs)
{
	unsigned	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	destroy_textures(t_vars *v)
{
	if (v->textures.east.width)
		mlx_destroy_image(v->mlx, v->textures.east.img.img);
	if (v->textures.west.width)
		mlx_destroy_image(v->mlx, v->textures.west.img.img);
	if (v->textures.north.width)
		mlx_destroy_image(v->mlx, v->textures.north.img.img);
	if (v->textures.sprite.width)
		mlx_destroy_image(v->mlx, v->textures.sprite.img.img);
	if (v->textures.south.width)
		mlx_destroy_image(v->mlx, v->textures.south.img.img);
}

void	free_first_image_colors(t_bmp_color **first_image_colors)
{
	unsigned	i;

	if (!first_image_colors)
		return ;
	i = 0;
	while (first_image_colors[i])
	{
		free(first_image_colors[i]);
		i++;
	}
	free(first_image_colors);
}

void	malloc_first_image_colors(t_vars *v)
{
	unsigned	i;

	if (!(v->first_image_colors = malloc(sizeof(char)
					* (1 + 3 * v->res.x * v->res.y))))
		error("Malloc failed", v, ERROR, NULL);
	i = 0;
	while (i < v->res.y)
		if (!(v->first_image_colors[i++] = malloc(sizeof(t_bmp_color)
						* (v->res.x))))
			error("Malloc failed", v, ERROR, NULL);
	v->first_image_colors[i] = NULL;
}
