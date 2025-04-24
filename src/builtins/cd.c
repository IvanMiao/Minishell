/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:25:44 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/23 19:21:26 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static char	*if_options_cd(char *str)
{
	static char	options[3];

	if (str[0] == '-' && str[1] == '-' && str[2])
	{
		options[0] = '-';
		options[1] = '-';
		options[2] = str[2];
		options[3] = '\0';
		return (options);
	}
	return (0);
}

static char	*check_cd_options(t_token *token, t_env *env, int *ret)
{
	char	*path;
	char	*invalid;

	invalid = if_options_cd(token->next->str);
	if (invalid)
	{
		ft_fprintf(2, "minishell: cd: --: invalid option\n", NULL);
		*ret = 2;
		return (NULL);
	}
	path = ft_get_env(env, "HOME");
	if (!path)
	{
		ft_fprintf(2, "minishell: cd: HOME not set\n", NULL);
		*ret = 1;
		return (NULL);
	}
	if (ft_strlen(path) == 0)
	{
		*ret = 0;
		return (NULL);
	}
	return (path);
}

static char	*get_cd_path(t_token *token, t_env *env, int *ret)
{
	while (token && (token->type != WORD || token->type != DOLLAR))
		token = token->next;
	if (token->next == NULL)
		return (ft_get_env(env, "HOME"));
	if (ft_strncmp(token->next->str, "~", 2) == 0
		|| ft_strncmp(token->next->str, "-", 2) == 0)
		return (check_cd_options(token, env, ret));
	return (token->next->str);
}

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	token = token->next;
	while (token && token->type != PIPE)
	{
		if ((token->type == WORD || token->type == DOLLAR) && ft_strncmp(token->str, "cd", 3))
			count++;
		token = token->next;
	}
	return (count);
}

int	ft_cd(t_token *token, t_env *env)
{
	char	*path;
	int		ret;
	DIR		*dir_fd;

	if (count_args(token) > 1)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n", NULL);
		return (1);
	}
	ret = 0;
	path = get_cd_path(token, env, &ret);
	if (ret != 0 || !path)
		return (ret);
	dir_fd = opendir(path);
	if (dir_fd == NULL && access(path, F_OK) == 0)
	{
		ft_fprintf(2, "minishell: cd: %s: Not a directory\n", path);
		return (1);
	}
	closedir(dir_fd);
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