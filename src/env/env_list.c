/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:32:46 by ymiao             #+#    #+#             */
/*   Updated: 2025/03/31 15:42:22 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static unsigned int	get_delim(char *content)
{
	int		distance;
	char	*name;

	name = ft_strchr(content, '=');
	if (!name)
		return (-1);
	distance = name - content;
	return (distance);
}

t_env	*env_lstnew(char *content)
{
	t_env	*new;
	int		start;

	new = malloc(sizeof(t_env) * 1);
	if (!new)
		return (NULL);
	start = get_delim(content);
	new -> content = content;
	new -> name = ft_substr(content, 0, start);
	new -> word = ft_substr(content, start + 1, ft_strlen(content) - start);
	new -> next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *lst)
{
	t_env	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current -> next)
		current = current -> next;
	return (current);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = env_lstlast(*lst);
	last -> next = new;
}

void	env_lstdelone(t_env **lst, t_env *target)
{
	t_env	*current;

	if (!lst || !*lst || !target)
		return ;
	if (*lst == target)
	{
		*lst = target->next;
		free(target->name);
		free(target->word);
		free(target);
		return ;
	}
	current = *lst;
	while (current && current->next != target)
		current = current->next;
	if (current && current->next == target)
	{
		current->next = target->next;
		free(target->name);
		free(target->word);
		free(target);
	}
}
