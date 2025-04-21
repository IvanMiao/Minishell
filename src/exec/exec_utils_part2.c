/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_part2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:51:42 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/21 19:46:32 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	is_directory(t_cmd *cmd)
{
	struct stat	info;

	if (stat(cmd->pathname, &info) != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
		ft_fprintf(2, "minishell: %s: Is a directory\n", cmd->pathname);
	return (S_ISDIR(info.st_mode));
}

int	file_nonexist(t_cmd *cmd)
{
	if (ft_strchr(cmd->pathname, '/'))
	{
		if (access(cmd->pathname, X_OK | F_OK))
		{
			ft_fprintf(2, "minishell: ", NULL);
			perror(cmd->pathname);
			return(126);
		}
	}
	return (0);
}

int	check_cmd(t_cmd *cmd, t_token *token, t_env *env)
{
	if (!cmd->pathname && cmd->delimiter)
	{
		handle_here_doc(token, env, cmd);
		unlink("./.heredoc.tmp");
		if (cmd->open_error == true)
			return (1);
		return (0);
	}
	if (cmd->open_error == true)
		return (1);
	if (!cmd->pathname)
		return (0);
	if (is_directory(cmd))
		return (126);
	if (file_nonexist(cmd))
		return (127);
	return (-1);
}
