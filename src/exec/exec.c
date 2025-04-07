/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:35:08 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 14:07:14 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*find_full_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*result;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			return (NULL);
		result = ft_strjoin(full_path, cmd);
		free(full_path);
		if (!result)
			return (NULL);
		if (access(result, F_OK) == 0)
			return (result);
		free(result);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	*found_path;
	char	*full_exec;
	char	**result;
	int		i;

	found_path = ft_get_env(env, "PATH");
	if (found_path)
	{
		result = ft_split(found_path, ':');
		if (!result)
			return (NULL);
		full_exec = find_full_path(cmd, result);
		i = 0;
		while (result[i])
			free(result[i++]);
		free(result);
		return (full_exec);
	}
	return (NULL);
}

void	ft_exec(char *cmd_shell, t_env *env, t_cmd *cmd)
{
	char	**all_cmd;
	char	*path;

	all_cmd = ft_split(cmd_shell, ' ');
	if (all_cmd == NULL || all_cmd[0] == NULL)
	{
		ft_free(all_cmd);
		exit(EXIT_FAILURE);
	}
	path = find_path(all_cmd[0], env);
	if (path == NULL)
	{
		ft_free(all_cmd);
		exit(127);
	}
	if (execve(cmd->pathname, cmd->argv, cmd->envp) == -1)
	{
		ft_free(all_cmd);
		free(path);
		errors(5);
	}
	free(path);
	ft_free(all_cmd);
}
