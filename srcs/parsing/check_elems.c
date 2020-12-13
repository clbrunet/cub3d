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
	if (v->res.x == 0)
		error("Resolution missing", v, ERROR, NULL);
	else if (!v->textures.north.width)
		error("North texture missing", v, ERROR, NULL);
	else if (!v->textures.south.width)
		error("South texture missing", v, ERROR, NULL);
	else if (!v->textures.west.width)
		error("West texture missing", v, ERROR, NULL);
	else if (!v->textures.east.width)
		error("East texture missing", v, ERROR, NULL);
	else if (!v->textures.sprite.width)
		error("Sprite texture missing", v, ERROR, NULL);
	else if (v->colors.floor.full == (unsigned)-1)
		error("Floor color missing", v, ERROR, NULL);
	else if (v->colors.ceilling.full == (unsigned)-1)
		error("Ceilling color missing", v, ERROR, NULL);
}
