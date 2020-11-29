/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:49:28 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:49:28 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*dup_bp;

	if (!(dup = malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return ((char *)NULL);
	dup_bp = dup;
	while (*s1)
	{
		*dup = *s1;
		dup++;
		s1++;
	}
	*dup = 0;
	return (dup_bp);
}
