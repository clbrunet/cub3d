/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:09:29 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/28 18:25:23 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int		main(void)
{
	void	*mlx_ptr;
	mlx_ptr = mlx_init();
	mlx_new_window(mlx_ptr, 500, 500, "Cub3D");
	mlx_loop(mlx_ptr);
	return (0);
}
