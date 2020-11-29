/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbrunet <clbrunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:53:30 by clbrunet          #+#    #+#             */
/*   Updated: 2020/11/16 13:53:30 by clbrunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned	ft_lstsize_free_last(t_list *lst, void (*del)(void *))
{
	t_list		*iter;
	unsigned	iter_nb;

	iter_nb = 0;
	iter = lst;
	while (iter->next)
	{
		iter_nb++;
		iter = iter->next;
	}
	(*del)(iter->content);
	free(iter);
	return (iter_nb);
}

void			ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*iter;
	unsigned	iter_nb;
	unsigned	i;

	if (!lst || !del || !*lst)
		return ;
	iter_nb = ft_lstsize_free_last(*lst, del);
	while (iter_nb)
	{
		iter = *lst;
		i = 0;
		while (i < iter_nb - 1)
		{
			iter = iter->next;
			i++;
		}
		(*del)(iter->content);
		free(iter);
		iter_nb--;
	}
	*lst = (t_list *)NULL;
}
