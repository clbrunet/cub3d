/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:09:29 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/13 10:36:59 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>

#include "parsing.h"
#include "hooks.h"
#include "raycasting.h"
#include "draw.h"

void		error(char const *const error_msg, t_vars *v, t_error const error,
		void *to_free)
{
	if (to_free)
		free(to_free);
	free_strs(v->map.grid);
	destroy_textures(v);
	free_first_image_colors(v->first_image_colors);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
	if (v->img.img)
		mlx_destroy_image(v->mlx, v->img.img);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	ft_putendl_fd("Error", 2);
	if (error == PERROR)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, 2);
	exit(1);
}

int			end(t_vars *v)
{
	mlx_loop_end(v->mlx);
	return (0);
}

static void	game(char const *const scene_path)
{
	t_vars	v;

	initialize_parsing(&v);
	if (!(v.mlx = mlx_init()))
		error("Connection between software and display failed", &v, ERROR,
				NULL);
	check_av(scene_path, NULL, &v);
	parse_scene(scene_path, &v);
	initialize_mlx(&v);
	v.pixel_put_ft = &mlx_img_pixel_put;
	mlx_loop(v.mlx);
	free_strs(v.map.grid);
	mlx_destroy_window(v.mlx, v.win);
	destroy_textures(&v);
	mlx_destroy_image(v.mlx, v.img.img);
	mlx_destroy_display(v.mlx);
	free(v.mlx);
	ft_putendl_fd("Game exited", 1);
}

static void	save(char const *const scene_path, char const *const save_flag)
{
	t_vars		v;

	initialize_parsing(&v);
	if (!(v.mlx = mlx_init()))
		error("Connection between software and display failed", &v, ERROR,
				NULL);
	check_av(scene_path, save_flag, &v);
	parse_scene(scene_path, &v);
	v.pixel_put_ft = &bmp_data_pixel_put;
	malloc_first_image_colors(&v);
	cast_rays(&v);
	draw_hud(&v);
	write_bmp(&v);
	free_strs(v.map.grid);
	free_first_image_colors(v.first_image_colors);
	destroy_textures(&v);
	mlx_destroy_display(v.mlx);
	free(v.mlx);
	ft_putendl_fd("./save.bmp created", 1);
}

int			main(int ac, char **av)
{
	if (ac == 2)
		game(av[1]);
	else if (ac == 3)
		save(av[1], av[2]);
	else
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	return (0);
}
