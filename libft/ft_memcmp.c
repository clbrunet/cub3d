/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:44:01 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:44:01 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us_s1;
	const unsigned char	*us_s2;

	if (!n)
		return (0);
	us_s1 = (unsigned char *)s1;
	us_s2 = (unsigned char *)s2;
	while (*us_s1 == *us_s2 && --n)
	{
		us_s1++;
		us_s2++;
	}
	return ((int)(*us_s1 - *us_s2));
}
