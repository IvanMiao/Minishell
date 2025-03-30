/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:01:14 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/18 01:03:35 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*i;
	t_list	*ans;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	i = lst;
	ans = NULL;
	while (i)
	{
		new = ft_lstnew(f(i -> content));
		if (!new)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&ans, new);
		i = i -> next;
	}
	return (ans);
}
