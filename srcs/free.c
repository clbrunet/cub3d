/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 06:38:37 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/30 06:38:37 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_strs(char **strs)
{
	int		i;

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

void		free_config(t_config *config)
{
	free(config->textures.north);
	free(config->textures.south);
	free(config->textures.west);
	free(config->textures.east);
	free(config->textures.sprite);
}
