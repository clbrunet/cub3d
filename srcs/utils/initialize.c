/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:19:51 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/15 17:01:55 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "utils.h"
#include "hooks.h"

void	initialize_parsing(t_vars *v)
{
	v->res.x = 0;
	v->res.y = 0;
	v->textures.north.width = 0;
	v->textures.north.width = 0;
	v->textures.south.width = 0;
	v->textures.west.width = 0;
	v->textures.east.width = 0;
	v->textures.regeneration.width = 0;
	v->textures.health.width = 0;
	v->textures.monster.width = 0;
	v->textures.floor.width = 0;
	v->textures.ceilling.width = 0;
	v->fog.full = (unsigned)-1;
	v->map.grid = NULL;
	v->first_image_colors = NULL;
	v->win = NULL;
	v->mlx = NULL;
	v->img.img = NULL;
	v->weapon_state = 0;
	v->textures.weapon[0].width = 0;
	v->textures.weapon[1].width = 0;
	v->textures.weapon[2].width = 0;
	v->textures.weapon[3].width = 0;
	v->textures.weapon[4].width = 0;
	v->textures.weapon[5].width = 0;
}

void	initialize_mlx(t_vars *v)
{
	if (!(v->win = mlx_new_window(v->mlx, v->res.x, v->res.y,
					"Cub3D")))
		error("Window creation failed", v, ERROR, NULL);
	if (!(v->img.img = mlx_new_image(v->mlx, v->res.x, v->res.y)))
		error("Image creation failed", v, ERROR, NULL);
	v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bits_per_pixel,
			&v->img.line_length, &v->img.endian);
	mlx_loop_hook(v->mlx, &loop_hook, v);
	initialize_keys(&v->keys);
	mlx_hook(v->win, KeyPress, KeyPressMask, &keypress_hook, v);
	mlx_hook(v->win, KeyRelease, KeyReleaseMask, &keyrelease_hook, v);
	mlx_hook(v->win, ClientMessage, StructureNotifyMask, &end, v);
}

void	initialize_keys(t_keys *keys)
{
	keys->left = 0;
	keys->right = 0;
	keys->z = 0;
	keys->q = 0;
	keys->s = 0;
	keys->d = 0;
	keys->lshift = 0;
	keys->up = 0;
	keys->down = 0;
	keys->lctrl = 0;
	keys->f = 0;
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
