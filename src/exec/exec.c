/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:05:52 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/18 03:53:43 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static void	all_dups(t_cmd *cmd, int *prev_pipe)
{
	int	fd_in;
	int	fd_out;

	if (prev_pipe == NULL)
		fd_in = -1;
	else
		fd_in = *prev_pipe;
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->delimiter)
	{
		fd_in = open("./.heredoc.tmp", O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
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

int	exec_simple_cmd(t_token *token, t_env *env)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		status;
	int		exit_builtin;

	cmd = set_cmd(token, env);
	// printf("------------------------------\n");
	// printf(GREEN"cmd path is: %s\n"ENDCOLOR, cmd->pathname);
	// printf("infile is: %s\n", cmd->infile);
	// printf("outfile is: %s\n", cmd->outfile);
	// printf("delimiter is: %s\n", cmd->delimiter);
	// printf("append?: %s\n", cmd->append? "true" : "false");
	// printf("------------------------------\n");
	if (!cmd->pathname && cmd->delimiter)
	{
		handle_here_doc(token, env, cmd);
		return (free_cmd(cmd), 0);
	}
	exit_builtin = exec_builtin_parent(cmd, env, token);
	if (exit_builtin != -1)
		return (free_cmd(cmd), exit_builtin);
	pid = fork();
	if (pid == 0)
	{
		sig_in_child();
		handle_here_doc(token, env, cmd);
		all_dups(cmd, NULL);
		if (exec_builtin_child(cmd, env, token) != -1 || !cmd->pathname)
		{
			free_all(env, token, cmd);
			exit(0);
		}
		execve(cmd->pathname, cmd->argv, cmd->envp);
		error_execve(cmd, env, token);
	}
	sig_in_parent(1);
	waitpid(pid, &status, 0);
	sig_in_parent(2);
	if (cmd->delimiter)
		unlink("./.heredoc.tmp");
	free_cmd(cmd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	exec_child(t_token *token, t_env *env, t_cmd *cmd)
{
	int	exit_builtin;
	
	sig_in_child();
	handle_here_doc(token, env, cmd);
	all_dups(cmd, NULL);
	exit_builtin = exec_builtin(cmd, env, token);
	if (exit_builtin != -1)
	{
		free_all(env, token, cmd);
		exit (0);
	}
	if (execve(cmd->pathname, cmd->argv, cmd->envp) < 0)
		error_execve(cmd, env, token);
	return (1);
}

pid_t	last_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	t_cmd	*cmd;
	pid_t	pid;

	cmd = set_cmd(token, env);
	if (!cmd->pathname && cmd->delimiter)
	{
		handle_here_doc(token, env, cmd);
		return (free_cmd(cmd), 0);
	}
	pid = fork();
	if (pid == -1)
		errors(3);
	if (pid == 0)
	{
		if (*prev_pipe != -1 && dup2(*prev_pipe, STDIN_FILENO) == -1)
			errors(1); // need to free all
		if (*prev_pipe != -1)
			close(*prev_pipe);
		exec_child(token, env, cmd);
	}
	sig_in_parent(1);
	if (cmd->delimiter)
		unlink("./.heredoc.tmp");
	free_cmd(cmd);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	return (pid);
}
