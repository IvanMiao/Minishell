/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:24:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/04 18:18:47 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/* check if it is a unvalid identifier */
static int	check_newenv(char *arg)
{
	char	*name;
	int		distance;
	int		i;

	i = 0;
	name = ft_strchr(arg, '=');
	distance = name - arg;
	if (arg[i] != '_' && !ft_isalpha(arg[i]))
	{
		ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", arg);
		return (FAIL);
	}
	while (i < distance)
	{
		if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n",
				arg);
			return (FAIL);
		}
		i++;
	}
	return (distance);
}

static int	replace_env(t_env *copy, char *arg)
{
	int		start;
	char	*name;

	name = ft_strchr(arg, '=');
	start = name - arg;
	free(copy->content);
	free(copy->name);
	free(copy->word);
	copy->content = ft_strdup(arg);
	copy->name = ft_substr(arg, 0, start);
	copy->word = ft_substr(arg, start + 1, ft_strlen(arg) - start);
	return (0);
}

/* 
	return immediately if there isn't a '=' in argument.
	add a node to t_env if everything is ok,
	replace the content if two names are the same 
*/
int	ft_export(t_env *env, char *argument)
{
	t_env	*new;
	t_env	*copy;
	int		dist_arg;
	int		dist_now;

	if (!ft_strchr(argument, '='))
		return (1);
	copy = env;
	dist_arg = check_newenv(argument);
	if (dist_arg == FAIL)
		return (1);
	while (copy)
	{
		dist_now = ft_strchr(copy->content, '=') - copy->content;
		if (dist_now == dist_arg
			&& !ft_strncmp(argument, copy->content, dist_arg))
		{
			replace_env(copy, argument);
			return (0);
		}
		copy = copy->next;
	}
	new = env_lstnew(argument);
	env_lstadd_back(&env, new);
	return (0);
}

/* test */
/*
int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	env = set_env(envp);
	if (ft_export(env, av[1]))
		return (1);
	printf("seccess\n");
	//ft_env(env);
	return (0);
}
*/
