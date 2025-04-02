/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:30:05 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/02 16:39:00 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static int	check_arg(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] == SPACE || arg[i] == TAB)
		i++;
	if (arg[i] != '_' && !ft_isalpha(arg[i]))
	{
		ft_fprintf(2, "minishell: unset: '%s': not a valid identifier\n", arg);
		return (FAIL);
	}
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			ft_fprintf(2, "minishell: unset: '%s': not a valid identifier\n", arg);
			return (FAIL);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_env *env, char *argument)
{
	t_env	*copy;
	int		size;

	copy = env;
	size = ft_strlen(argument);
	if (check_arg(argument) == FAIL)
		return (1);
	while (copy)
	{
		if (size == (int)ft_strlen(copy->name)
			&& ft_strncmp(argument, copy->name, size) == 0)
		{
			env_lstdelone(&env, copy);
			return (0);
		}
		copy = copy->next;
	}
	return (0);
}

/* test */
/*
int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	env = set_env(envp);
	if (ft_unset(env, av[1]))
		return (1);
	printf("seccess\n");
	ft_env(env);
	return (0);
}
*/
