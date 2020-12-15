/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 13:19:40 by clbrunet          #+#    #+#             */
/*   Updated: 2020/12/14 19:02:48 by clbrunet         ###   ########.fr       */
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
	else if (!v->textures.monster.width)
		error("Monster texture missing", v, ERROR, NULL);
	else if (!v->textures.regeneration.width)
		error("Regeneration texture missing", v, ERROR, NULL);
	else if (!v->textures.health.width)
		error("Health texture missing", v, ERROR, NULL);
	else if (!v->textures.floor.width)
		error("Floor texture missing", v, ERROR, NULL);
	else if (!v->textures.ceilling.width)
		error("Ceilling texture missing", v, ERROR, NULL);
}
