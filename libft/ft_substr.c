/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:53:51 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 15:17:43 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strvoid(void)
{
	char	*strvoid;

	if (!(strvoid = malloc(sizeof(char))))
		return ((char *)NULL);
	*strvoid = 0;
	return (strvoid);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	char		*sub_bp;
	unsigned	s_len;

	if (!s)
		return ((char *)NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strvoid());
	s += start;
	s_len -= start;
	if (s_len < len)
		len = s_len;
	if (!(sub = malloc(((len + 1) * sizeof(char)))))
		return ((char *)NULL);
	sub_bp = sub;
	while (len--)
	{
		*sub = *s;
		sub++;
		s++;
	}
	*sub = '\0';
	return (sub_bp);
}
