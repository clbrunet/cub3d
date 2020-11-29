/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:53:46 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:53:46 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	char	*joint_bp;

	if (!s1 || !s2)
		return (NULL);
	if (!(joint = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	joint_bp = joint;
	while (*s1)
	{
		*joint = *s1;
		joint++;
		s1++;
	}
	while (*s2)
	{
		*joint = *s2;
		joint++;
		s2++;
	}
	*joint = 0;
	return (joint_bp);
}
