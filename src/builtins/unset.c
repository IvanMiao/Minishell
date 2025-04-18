/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:30:05 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 22:57:17 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static bool	check_first_c(char *arg)
{
	if (*arg == '\0')
	{
		ft_fprintf(2, "minishell: export: `': not a valid identifier\n", NULL);
		return (false);
	}
	if (*arg == '-' && *(arg + 1))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(*arg, 2);
		ft_putchar_fd(*(arg + 1), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (false);
	}
	if (*arg != '_' && !ft_isalpha(*arg))
	{
		ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", arg);
		return (false);
	}
	return (true);
}

static int	check_arg(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] == SPACE || arg[i] == TAB)
		i++;
	if (!check_first_c(arg))
		return (FAIL);
	if (arg[i] != '_' && !ft_isalpha(arg[i]))
	{
		ft_fprintf(2, "minishell: unset: '%s': not a valid identifier\n", arg);
		return (FAIL);
	}
	while (arg[i])
	{
		if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			ft_fprintf(2, "minishell: unset: '%s': not a valid identifier\n",
				arg);
			return (FAIL);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_env *env, t_token *token)
{
	char	*argument;
	t_env	*copy;
	int		size;

	if (!token || !token->next)
		return (0);
	argument = token->next->str;
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
