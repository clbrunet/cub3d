/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:09:29 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/01 15:45:28 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"
#include "parsing.h"
#include "hooks.h"

void		error(char const *const error_msg, t_vars *v, t_error const error)
{
	free(v->mlx);
	/* free_textures(&v->textures); */
	/* free_strs(v->map.grid); */
	ft_putendl_fd("Error", 2);
	if (error == PERROR)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, 2);
	exit(1);
}

void	initialize_mlx(t_vars *v)
{
	if (!(v->win = mlx_new_window(v->mlx, v->res.x, v->res.y,
					"Cub3D")))
		error("Window creation failed", v, ERROR);
	if (!(v->img.img = mlx_new_image(v->mlx, v->res.x, v->res.y)))
		error("Image creation failed", v, ERROR);
	v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bits_per_pixel,
			&v->img.line_length, &v->img.endian);
	mlx_loop_hook(v->mlx, &loop_hook, v);
	initialize_keys(&v->keys);
	mlx_hook(v->win, KeyPress, KeyPressMask, &keypress_hook, v);
	mlx_hook(v->win, KeyRelease, KeyReleaseMask, &keyrelease_hook, v);
}

static void	game(char const *const scene_path)
{
	t_vars	v;

	initialize_parsing(&v);
	if (!(v.mlx = mlx_init()))
		error("Connection between software and display failed", &v, ERROR);
	check_av(scene_path, NULL, &v);
	parse_scene(scene_path, &v);
	initialize_mlx(&v);
	mlx_loop(v.mlx);
	/* free_strs(v.map.grid); */
	/* mlx_destroy_window(v.mlx, v.win); */
	/* mlx_destroy_image(v.mlx, v.img.img); */
	/* free(v.mlx); */
}

static void	save(char const *const scene_path, char const *const save_flag)
{
	t_vars	v;

	initialize_parsing(&v);
	v.mlx = NULL;
	check_av(scene_path, save_flag, &v);
	parse_scene(scene_path, &v);
	/* initialize_mlx(&v); */
	/* free_strs(v.map.grid); */
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
