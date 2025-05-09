/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:16:15 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/29 04:56:15 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

t_token	*token_lst(char *str, t_tokentype type, int value)
{
	t_token	*token;

	token = (t_token *)mem_manager(MALLOC, sizeof(t_token), NULL);
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	token->value = value;
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

t_token	*token_lstlast(t_token *lst)
{
	t_token	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current -> next)
		current = current -> next;
	return (current);
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = token_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

void	token_lstclear(t_token **lst)
{
	t_token	*temp;

	while ((*lst)->prev)
		(*lst) = (*lst)->prev;
	while (*lst)
	{
		temp = (*lst)->next;
		mem_manager(FREE, 0, (*lst)->str);
		mem_manager(FREE, 0, *lst);
		*lst = temp;
	}
}
