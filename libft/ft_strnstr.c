/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:47:48 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:47:48 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*needle_bp;
	int			tested_char;

	if (!*needle)
		return ((char *)haystack);
	needle_bp = needle;
	while (*haystack && len)
	{
		while (len && *haystack && *haystack == *needle)
		{
			haystack++;
			needle++;
			len--;
		}
		tested_char = needle - needle_bp;
		if (!*needle)
			return ((char *)(haystack - tested_char));
		haystack -= tested_char - 1;
		len += tested_char - 1;
		needle = needle_bp;
	}
	return (NULL);
}
