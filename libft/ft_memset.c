/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:42:23 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:42:23 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*s_b;
	unsigned char	uc_c;

	s_b = (char *)b;
	uc_c = (char)c;
	while (len--)
		*(s_b++) = uc_c;
	return (b);
}
