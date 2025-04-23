/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_part2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:51:42 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/23 11:45:08 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	is_directory(t_cmd *cmd)
{
	struct stat	info;

	if (stat(cmd->name, &info) != 0)
		return (0);
	if (S_ISDIR(info.st_mode))
		ft_fprintf(2, "minishell: %s: Is a directory\n", cmd->name);
	return (S_ISDIR(info.st_mode));
}

int	file_nonexist(t_cmd *cmd)
{
	if (ft_strchr(cmd->name, '/'))
	{
		if (access(cmd->name, F_OK | X_OK))
		{
			ft_fprintf(2, "minishell: ", NULL);
			perror(cmd->name);
			if (errno == EACCES)
				return (126);
			else if (errno == ENOENT)
				return (127);
		}
	}
	return (0);
}

int	check_cmd(t_cmd *cmd, t_token *token, t_env *env)
{
	int	code;

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
	code = file_nonexist(cmd);
	if (code)
		return (code);
	return (-1);
}

void	all_dups2(t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	if (cmd->infile)
	{
		fd_in = open_file(cmd->infile, 0);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->outfile && cmd->append == false)
	{
		fd_out = open_file(cmd->outfile, 1);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->outfile && cmd->append == true)
	{
		fd_out = open_file(cmd->outfile, 2);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	all_dups(t_cmd *cmd, int *prev_pipe)
{
	int	fd_in;

	if (prev_pipe == NULL)
		fd_in = -1;
	else
		fd_in = *prev_pipe;
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->delimiter[0])
	{
		fd_in = open("./.heredoc.tmp", O_RDONLY);
		if (fd_in == -1)
			perror("open");
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	all_dups2(cmd);
}
