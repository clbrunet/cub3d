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

#include "cub3d.h"
#include "free.h"
#include "parsing.h"

void	error(char const *const error_msg, t_vars *v, t_error const error)
{
	free(v->mlx);
	free_textures(&v->textures);
	free_strs(v->map.grid);
	ft_putendl_fd("Error", 2);
	if (error == PERROR)
		perror(error_msg);
	else
		ft_putendl_fd(error_msg, 2);
	exit(1);
}


static void	check_av(char const *scene_path, char const *save_flag, t_vars *v)
{
	unsigned	len;

	len = ft_strlen(scene_path);
	if (len < 4)
		error("Wrong scene file extension", v, ERROR);
	scene_path += len - 4;
	if (!ft_strnstr(scene_path, ".cub", 4))
		error("Wrong scene file extension", v, ERROR);
	if (save_flag && (ft_strlen(save_flag) != 6
				|| !ft_strnstr(save_flag, "--save", 6)))
		error("Second parameter must be \"--save\"", v, ERROR);
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
	free_textures(&v.textures);
	free_strs(v.map.grid);
	mlx_destroy_window(v.mlx, v.win);
	mlx_destroy_image(v.mlx, v.img.img);
	free(v.mlx);

}

static void	save(char const *const scene_path, char const *const save_flag)
{
	t_vars	v;

	initialize_parsing(&v);
	v.mlx = NULL;
	check_av(scene_path, save_flag, &v);
	parse_scene(scene_path, &v);
	initialize_mlx(&v);
	free_textures(&v.textures);
	free_strs(v.map.grid);
}

int		main(int ac, char **av)
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
