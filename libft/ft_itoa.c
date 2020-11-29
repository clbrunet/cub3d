/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:50:57 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:50:57 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned	ft_nlen(long n, int len)
{
	if (n > 9)
		return (ft_nlen(n / 10, len + 1));
	return (len);
}

static void		ft_itoa_conv(char *a, long n)
{
	if (n > 9)
		ft_itoa_conv(a - 1, n / 10);
	*a = n % 10 + '0';
}

char			*ft_itoa(int n)
{
	char		*a;
	long		l_n;
	unsigned	len;
	int			is_negative;

	l_n = (long)n;
	is_negative = 0;
	if (l_n < 0)
	{
		l_n *= -1;
		is_negative = 1;
	}
	len = ft_nlen(l_n, is_negative + 1);
	if (!(a = malloc((len + 1) * sizeof(char))))
		return ((char *)NULL);
	a[len] = 0;
	if (is_negative)
		*a = '-';
	ft_itoa_conv(a + len - 1, l_n);
	return (a);
}
