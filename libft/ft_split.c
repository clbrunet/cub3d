/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:53:38 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/19 13:43:52 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_split_by_zero(char const *s)
{
	char	**strs;

	if (!(strs = malloc(2 * sizeof(char *))))
		return ((char **)NULL);
	if (!(strs[0] = ft_strdup(s)))
		return ((char **)NULL);
	strs[1] = (char *)NULL;
	return (strs);
}

static unsigned	ft_count_strs(char const *s, char c)
{
	unsigned	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
			s++;
		count++;
	}
	if (s[-1] == c)
		count--;
	return (count);
}

static int		ft_malloc_strs(char **strs, char const *s, char c,
		unsigned count)
{
	unsigned	i;
	char const	*str_cp;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		str_cp = s;
		while (*s && *s != c)
			s++;
		if (!(strs[i] = malloc(((s - str_cp) + 1) * sizeof(char))))
			return (0);
		i++;
	}
	return (1);
}

static void		ft_fill_strs(char **strs, char const *s, char c,
		unsigned count)
{
	unsigned	i;
	unsigned	j;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		j = 0;
		while (*s && *s != c)
		{
			strs[i][j] = *s;
			s++;
			j++;
		}
		strs[i][j] = 0;
		i++;
	}
	strs[i] = (char *)NULL;
}

char			**ft_split(char const *s, char c)
{
	char		**strs;
	unsigned	count;

	if (!s)
		return ((char **)NULL);
	if (!*s)
	{
		if (!(strs = malloc(sizeof(char *))))
			return ((char **)NULL);
		strs[0] = (char *)NULL;
		return (strs);
	}
	if (!c)
		return (ft_split_by_zero(s));
	count = ft_count_strs(s, c);
	if (!(strs = malloc((count + 1) * sizeof(char *))))
		return ((char **)NULL);
	if (!ft_malloc_strs(strs, s, c, count))
		return ((char **)NULL);
	ft_fill_strs(strs, s, c, count);
	return (strs);
}
