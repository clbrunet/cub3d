/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:09:02 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/29 15:09:02 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		ft_atoitrim(char const **nptr)
{
	int		nb;

	if (!ft_isdigit(**nptr))
		return (0);
	nb = **nptr - '0';
	(*nptr)++;
	while (ft_isdigit(**nptr))
	{
		nb = nb * 10 + **nptr - '0';
		(*nptr)++;
	}
	return (nb);
}
