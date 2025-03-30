/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 03:21:12 by ymiao             #+#    #+#             */
/*   Updated: 2024/11/17 03:24:18 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		count;

	count = 0;
	current = lst;
	while (current)
	{
		count++;
		current = current -> next;
	}
	return (count);
}

/*
int	main(void)
{
	t_list * l =  NULL;
	if (ft_lstsize(l) == 0)
		printf("success\n");
	ft_lstadd_front(&l, ft_lstnew((void*)1));

	if (ft_lstsize(l) == 1)
		printf("success\n");
	ft_lstadd_front(&l, ft_lstnew((void*)2));

	if (ft_lstsize(l) == 2)
		printf("success");
	else
		printf("%d", ft_lstsize(l));
}
*/