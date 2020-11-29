/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:42:57 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/18 09:50:58 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*us_dst;
	const unsigned char	*us_src;
	unsigned char		uc_c;

	us_dst = (unsigned char *)dst;
	us_src = (unsigned char *)src;
	uc_c = (unsigned char)c;
	while (n--)
	{
		*us_dst = *(us_src++);
		if (*us_dst == uc_c)
			return ((void *)(us_dst + 1));
		us_dst++;
	}
	return (NULL);
}
