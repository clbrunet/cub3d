/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:43:06 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 14:17:22 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*s_dst;
	const char	*s_src;

	if (!dst && !src)
		return (dst);
	s_dst = (char *)dst;
	s_src = (char *)src;
	if (dst < src)
		while (len--)
			*(s_dst++) = *(s_src++);
	else
	{
		s_dst += len - 1;
		s_src += len - 1;
		while ((void *)s_dst >= dst)
			*(s_dst--) = *(s_src--);
	}
	return (dst);
}
