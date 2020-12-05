/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:19:40 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/05 13:19:40 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_elems(t_vars *v)
{
	if (v->res.x == -1)
		error("Resolution missing", v, ERROR);
	else if (!v->textures.north)
		error("North texture missing", v, ERROR);
	else if (!v->textures.south)
		error("South texture missing", v, ERROR);
	else if (!v->textures.west)
		error("West texture missing", v, ERROR);
	else if (!v->textures.east)
		error("East texture missing", v, ERROR);
	else if (!v->textures.sprite)
		error("Sprite texture missing", v, ERROR);
	else if (v->colors.floor.full == -1)
		error("Floor color missing", v, ERROR);
	else if (v->colors.ceilling.full == -1)
		error("Ceilling color missing", v, ERROR);
}

