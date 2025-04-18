/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:35:06 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/04 17:07:44 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

t_env	*set_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 1;
	if (envp && envp[0])
		env = env_lstnew(envp[0]);
	tmp = env;
	while (envp[i])
	{
		tmp->next = env_lstnew(envp[i]);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

int	ft_env(t_env *env)
{
	t_env	*copy;

	copy = env;
	while (copy)
	{
		printf("%s\n", copy->content);
		copy = copy->next;
	}
	return (0);
}

/* test */
/*
int	main()
{
	char **envp;
	t_env	*env;
	t_env	*tmp;
	
	envp = __environ;
	env = set_env(envp);
	ft_env(env);
	tmp = env;
	while (tmp)
	{
		printf("name: %s\tword: %s\n", tmp->name, tmp->word);
		tmp = tmp->next;
	}
	while(env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->word);
		free(tmp);
	}
	return (0);
}
*/