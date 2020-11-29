/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:42:47 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:42:47 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*s_dst;
	const char	*s_src;

	if (!dst && !src)
		return (dst);
	s_dst = (char *)dst;
	s_src = (char *)src;
	while (n--)
		*(s_dst++) = *(s_src++);
	return (dst);
}
