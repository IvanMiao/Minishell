/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:24:51 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/18 03:46:17 by ymiao            ###   ########.fr       */
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
		ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", arg);
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
	i = 0;
	while (i < distance)
	{
		if (arg[i] != '_' && !ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n",
				arg);
			return (-1);
		}
		i++;
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
	free(copy->content);
	free(copy->name);
	free(copy->word);
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
int	ft_export(t_env *env, t_token *token)
{
	t_env	*new;
	int		dist_arg;
	char	*arg;

	token = token->next;
	while (token && (token->type == DOLLAR || token->type == WORD))
	{
		arg = token->str;
		dist_arg = check_newenv(arg);
		if (dist_arg < 0 || check_env_replace(env, arg, dist_arg) == true)
		{
			token = token->next;
			continue ;
		}
		new = env_lstnew(arg);
		env_lstadd_back(&env, new);
		token = token->next;
	}
	if (dist_arg < 0)
		return (-dist_arg);
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
