/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 09:57:41 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/29 10:03:32 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialization.h"

void	initialize_config(t_config *config)
{
	config->res.x = -1;
	config->res.y = -1;
	config->textures.north = NULL;
	config->textures.south = NULL;
	config->textures.west = NULL;
	config->textures.east = NULL;
	config->textures.sprite = NULL;
	config->ceilling_color.full = -1;
	config->floor_color.full = -1;
}
