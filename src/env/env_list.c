/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:32:46 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/29 04:44:25 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static int	get_delim(char *content)
{
	int		distance;
	char	*name;

	name = ft_strchr(content, '=');
	if (!name)
		return (0);
	distance = name - content;
	return (distance);
}

t_env	*env_lstnew(char *content)
{
	t_env	*new;
	int		start;

	new = (t_env *)mem_manager(MALLOC, sizeof(t_env), NULL);
	if (!new)
		return (NULL);
	start = get_delim(content);
	new -> content = ft_strdup(content);
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
		mem_manager(FREE, 0, target->name);
		mem_manager(FREE, 0, target->word);
		mem_manager(FREE, 0, target->content);
		mem_manager(FREE, 0, target);
		return ;
	}
	current = *lst;
	while (current && current->next != target)
		current = current->next;
	if (current && current->next == target)
	{
		current->next = target->next;
		mem_manager(FREE, 0, target->name);
		mem_manager(FREE, 0, target->word);
		mem_manager(FREE, 0, target->content);
		mem_manager(FREE, 0, target);
	}
}
