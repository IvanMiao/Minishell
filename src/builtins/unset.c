/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:30:05 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/23 19:09:54 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static bool	check_first_c(char *arg)
{
	if (*arg == '\0')
	{
		ft_fprintf(2, "minishell: unset: `': not a valid identifier\n", NULL);
		return (false);
	}
	if (*arg == '-' && *(arg + 1))
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putchar_fd(*arg, 2);
		ft_putchar_fd(*(arg + 1), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (false);
	}
	if (*arg != '_' && !ft_isalpha(*arg))
	{
		ft_fprintf(2, "minishell: unset: '%s': not a valid identifier\n", arg);
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

static void	search_env(int size, t_env **env, char *arg)
{
	t_env	*curr;
	t_env	*next;

	curr = *env;
	while (curr)
	{
		next = curr->next;
		if (size == (int)ft_strlen(curr->name)
			&& ft_strncmp(arg, curr->name, size) == 0)
			env_lstdelone(env, curr);
		curr = next;
	}
}

int	ft_unset(t_env *env, t_cmd *cmd)
{
	int		size;
	int		i;
	int		code;

	if (cmd->argv && cmd->argv[0])
		i = 1;
	if (!cmd->argv || !(cmd->argv[0]))
		return (0);
	code = 0;
	while (cmd->argv[i])
	{
		size = ft_strlen(cmd->argv[i]);
		if (check_arg(cmd->argv[i]) == FAIL)
		{
			i++;
			code = 1;
			continue ;
		}
		search_env(size, &env, cmd->argv[i]);
		i++;
	}
	return (code);
}
