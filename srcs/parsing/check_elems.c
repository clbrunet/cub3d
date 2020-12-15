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

static void	check_elems2(t_vars *v)
{
	if (!v->textures.weapon[0].width)
		error("Weapon 0 texture missing", v, ERROR, NULL);
	else if (!v->textures.weapon[1].width)
		error("Weapon 1 texture missing", v, ERROR, NULL);
	else if (!v->textures.weapon[2].width)
		error("Weapon 2 texture missing", v, ERROR, NULL);
	else if (!v->textures.weapon[3].width)
		error("Weapon 3 texture missing", v, ERROR, NULL);
	else if (!v->textures.weapon[4].width)
		error("Weapon 4 texture missing", v, ERROR, NULL);
	else if (!v->textures.weapon[5].width)
		error("Weapon 5 texture missing", v, ERROR, NULL);
	else if (v->fog.full == (unsigned)-1)
		error("Fog color missing", v, ERROR, NULL);
}

void		check_elems(t_vars *v)
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
	else
		check_elems2(v);
}
