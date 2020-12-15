/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 06:38:37 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 14:00:06 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		free_strs(char **strs)
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

static void	destroy_weapon_textures(t_vars *v)
{
	if (v->textures.weapon[0].width)
		mlx_destroy_image(v->mlx, v->textures.weapon[0].img.img);
	if (v->textures.weapon[1].width)
		mlx_destroy_image(v->mlx, v->textures.weapon[1].img.img);
	if (v->textures.weapon[2].width)
		mlx_destroy_image(v->mlx, v->textures.weapon[2].img.img);
	if (v->textures.weapon[3].width)
		mlx_destroy_image(v->mlx, v->textures.weapon[3].img.img);
	if (v->textures.weapon[4].width)
		mlx_destroy_image(v->mlx, v->textures.weapon[4].img.img);
	if (v->textures.weapon[5].width)
		mlx_destroy_image(v->mlx, v->textures.weapon[5].img.img);
}

void		destroy_textures(t_vars *v)
{
	if (v->textures.east.width)
		mlx_destroy_image(v->mlx, v->textures.east.img.img);
	if (v->textures.west.width)
		mlx_destroy_image(v->mlx, v->textures.west.img.img);
	if (v->textures.north.width)
		mlx_destroy_image(v->mlx, v->textures.north.img.img);
	if (v->textures.south.width)
		mlx_destroy_image(v->mlx, v->textures.south.img.img);
	if (v->textures.regeneration.width)
		mlx_destroy_image(v->mlx, v->textures.regeneration.img.img);
	if (v->textures.health.width)
		mlx_destroy_image(v->mlx, v->textures.health.img.img);
	if (v->textures.monster.width)
		mlx_destroy_image(v->mlx, v->textures.monster.img.img);
	if (v->textures.floor.width)
		mlx_destroy_image(v->mlx, v->textures.floor.img.img);
	if (v->textures.ceilling.width)
		mlx_destroy_image(v->mlx, v->textures.ceilling.img.img);
	destroy_weapon_textures(v);
}

void		free_first_image_colors(t_bmp_color **first_image_colors)
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

void		malloc_first_image_colors(t_vars *v)
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
