/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:25:44 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/15 18:45:58 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	ft_cd(t_token *token, t_env *env)
{
	char	*path;
	int		argc;

	argc = count_args(token);
	if (argc > 1)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n", NULL);
		return (1);
	}
	if (token->next == NULL || ft_strncmp(token->next->str, "~", 1) == 0)
	{
		path = ft_get_env(env, "HOME");
		if (!path)
		{
			ft_fprintf(2, "minishell: cd: HOME not set\n", NULL);
			return (1);
		}
		if (ft_strlen(path) == 0)
			return (0);
	}
	else
		path = token->next->str;
	if (opendir(path) == 0)
	{
		ft_fprintf(2, "minishell: cd: %s: Not a directory\n", path);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_fprintf(2, "minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

/* test */
/*
int	main(int ac, char **av)
{
	char	*path;

	while (1)
	{
		path = readline("minishell$ ");
		if (strncmp(path, "cd ", 3) == 0)
			ft_cd(path + 3);
		getcwd(cwd, sizeof(cwd));
		if (strncmp(path, "stop", 4) == 0)
			return (0);
	}
	return (0);
}
*/