/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:24:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/29 04:44:07 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static int	check_first_c(char *arg)
{
	if (*arg == '\0')
	{
		ft_fprintf(2, "minishell: export: `': not a valid identifier\n", NULL);
		return (-1);
	}
	if (*arg == '-' && *(arg + 1))
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putchar_fd(*arg, 2);
		ft_putchar_fd(*(arg + 1), 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (-2);
	}
	if (*arg != '_' && !ft_isalpha(*arg))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", arg);
		return (-1);
	}
	return (0);
}

/* check if it is a unvalid identifier */
static int	check_newenv(char *arg)
{
	char	*name;
	int		distance;
	int		i;

	name = ft_strchr(arg, '=');
	if (!name)
		distance = (int)ft_strlen(arg);
	else
		distance = name - arg;
	i = check_first_c(arg);
	if (i < 0)
		return (i);
	i = -1;
	while (++i < distance)
	{
		if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
				arg);
			return (-1);
		}
	}
	if (!name)
		return (0);
	return (distance);
}

static int	replace_env(t_env *copy, char *arg)
{
	int		start;
	char	*name;

	name = ft_strchr(arg, '=');
	start = name - arg;
	mem_manager(FREE, 0, copy->content);
	mem_manager(FREE, 0, copy->name);
	mem_manager(FREE, 0, copy->word);
	copy->content = ft_strdup(arg);
	copy->name = ft_substr(arg, 0, start);
	copy->word = ft_substr(arg, start + 1, ft_strlen(arg) - start);
	return (0);
}

static bool	check_env_replace(t_env *env, char *arg, int dist_arg)
{
	t_env	*copy;
	bool	flag;

	copy = env;
	flag = false;
	if (dist_arg < 0)
		return (dist_arg);
	while (copy)
	{
		if ((int)ft_strlen(copy->name) == dist_arg
			&& !ft_strncmp(arg, copy->content, dist_arg))
		{
			replace_env(copy, arg);
			flag = true;
			break ;
		}
		copy = copy->next;
	}
	return (flag);
}

/* 
	add a node to t_env if everything is ok,
	replace the content if two names are the same 
*/
int	ft_export(t_env *env, t_cmd	*cmd)
{
	t_env	*new;
	int		i;
	int		dist_arg;

	if (cmd->argv && cmd->argv[0])
		i = 1;
	if (!(cmd->argv[i]))
		return (0);
	while (cmd->argv[i])
	{
		dist_arg = check_newenv(cmd->argv[i]);
		if (dist_arg <= 0
			|| check_env_replace(env, cmd->argv[i], dist_arg) == true)
		{
			i++;
			continue ;
		}
		new = env_lstnew(cmd->argv[i]);
		env_lstadd_back(&env, new);
		i++;
	}
	if (dist_arg < 0)
		return (-dist_arg);
	return (0);
}
