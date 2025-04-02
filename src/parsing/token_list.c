/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:16:15 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/02 10:51:49 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

t_token	*token_lst(char *str, t_tokentype type, int value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	token->value = value;
	token->type = type;
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
}

void	token_lstclear(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = temp;
	}
}
