/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:43:39 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/18 09:57:43 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*us_s;
	unsigned char			uc_c;

	if (!n)
		return (NULL);
	us_s = (unsigned char *)s;
	uc_c = (unsigned char)c;
	while (--n && *us_s != uc_c)
		us_s++;
	if (*us_s == uc_c)
		return ((void *)us_s);
	return (NULL);
}
