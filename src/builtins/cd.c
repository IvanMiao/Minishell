/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:25:44 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/24 18:15:35 by ymiao            ###   ########.fr       */
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

static char	*check_cd_options(char *arg, t_env *env, int *ret)
{
	char	*path;
	char	*invalid;

	invalid = if_options_cd(arg);
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

static char	*get_cd_path(char *arg, t_env *env, int *ret)
{
	if (arg == NULL)
		return (ft_get_env(env, "HOME"));
	if (ft_strncmp(arg, "~", 2) == 0
		|| ft_strncmp(arg, "-", 2) == 0)
		return (check_cd_options(arg, env, ret));
	return (arg);
}

static int	change_path(char *path)
{
	DIR	*dir_fd;

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

int	ft_cd(t_env *env, t_cmd *cmd)
{
	char	*path;
	int		ret;
	int		count;

	count = 0;
	while (cmd->argv[count])
		count++;
	if (count > 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n", NULL);
		return (1);
	}
	ret = 0;
	path = get_cd_path(cmd->argv[1], env, &ret);
	if (ret != 0 || !path)
		return (ret);
	return (change_path(path));
}
