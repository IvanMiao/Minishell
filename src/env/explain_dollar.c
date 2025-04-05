/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explain_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:53:46 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/04 17:35:25 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static t_env	*search_dollar(t_env *env, t_token *token)
{
	t_env	*copy;

	copy = env;
	while (copy)
	{
		if (ft_strlen(copy->name) == ft_strlen((token->str) + 1))
		{
			if (!ft_strncmp(copy->name, (token->str) + 1,
					ft_strlen(copy->name)))
				return (copy);
		}
		copy = copy->next;
	}
	return (NULL);
}

char	*explain_dollar(t_env *env, t_token *token)
{
	char	*ans;
	t_env	*target;

	if (token->type != DOLLAR)
		return (printf("It's not a env variable!\n"), NULL);
	target = search_dollar(env, token);
	if (target == NULL)
		return (NULL);
	else
	{
		ans = target->word;
		return (ans);
	}
}
