/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:35:08 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/04 16:24:22 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*find_full_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*result;
	int		i;

	i = 0;
	while (paths[i++] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
		{
			free(full_path);
			exit(EXIT_FAILURE);
		}
		result = ft_strjoin(full_path, cmd);
		if (!result)
		{
			free(result);
			exit(EXIT_FAILURE);
		}
		free(full_path);
		if (access(result, F_OK) == 0)
			return (result);
		free (result);
	}
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	char	*found_path;
	char	*full_exec;
	char	**result;
	int		i;

	i = 0;
	found_path = 0;
	while (envp[i++] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			found_path = envp[i] + 5;
			break ;
		}
	}
	if (found_path)
	{
		result = ft_split(found_path, ':');
		full_exec = find_full_path(cmd, result);
		i = 0;
		while (result[i])
			free (result[i++]);
		return (free(result), full_exec);
	}
	return (0);
}

void	ft_exec(char *cmd_shell, char **envp)
{
	char	**all_cmd;
	char	*path;

	all_cmd = ft_split(cmd_shell, ' ');
	if (all_cmd == NULL || all_cmd[0] == NULL)
	{
		ft_free(all_cmd);
		exit(EXIT_FAILURE);
	}
	path = find_path(*all_cmd, envp);
	if (path == NULL)
	{
		free(path);
		ft_free(all_cmd);
		exit(127);
	}
	if ((execve(path, all_cmd, envp)) == -1)
	{
		ft_free(all_cmd);
		free(path);
		errors(5);
	}
	free(path);
	ft_free(all_cmd);
}
