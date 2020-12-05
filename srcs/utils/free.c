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

void		free_textures(t_textures *textures)
{
	free(textures->north);
	free(textures->south);
	free(textures->west);
	free(textures->east);
	free(textures->sprite);
}
