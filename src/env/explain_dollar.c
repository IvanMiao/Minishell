/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explain_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:53:46 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/02 17:44:40 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static t_env	*search_dollar(t_env *env, t_token *token)
{
	while (env)
	{
		if (ft_strlen(env->name) != ft_strlen(token + 1))
		{
			env = env->next;
			continue ;
		}
		if (!ft_strncmp(env->name, token + 1, ft_strlen(env->name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*explain_dollar(t_env *env, t_token *token) // need test
{
	char	*ans;
	t_env	*target;

	if (token->type != DOLLAR)
		return(printf("It's not a env variable!\n"), 1);
	target = search_dollar(env, token);
	if (target == NULL)
		return (NULL);
	else
	{
		ans = target->word;
		return (ans);
	}
}