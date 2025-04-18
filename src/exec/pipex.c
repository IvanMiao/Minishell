/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:32 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/18 03:24:15 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	x_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	int		pipe_fd[2];
	pid_t	child;
	t_cmd	*cmd;

	cmd = set_cmd(token, env);
	if (!cmd->pathname && cmd->delimiter)
	{
		handle_here_doc(token, env, cmd);
		return (free_cmd(cmd), 0);
	}
	if (pipe(pipe_fd) == -1)
		errors(2);
	child = fork();
	if (child == -1)
		errors(3);
	if (child == 0)
	{
		if (*prev_pipe != -1 && dup2(*prev_pipe, STDIN_FILENO) == -1)
			errors(1); // need to free all
		if (*prev_pipe != -1)
			close(*prev_pipe);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			errors(1); // need to free all
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec_child(token, env, cmd);
	}
	sig_in_parent(1);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
	free_cmd(cmd);
	return (0);
}

int	exec_pipes(t_token *token, t_env *env, int *prev_pipe, int nb_cmd)
{
	t_token	*start;
	int		exit_code;
	pid_t	last_pid;
	int		status;

	start = token;
	exit_code = 0;
	while (token)
	{
		if (token->type == PIPE)
		{
			x_cmd(start, env, prev_pipe);
			start = token->next;
		}
		token = token->next;
	}
	last_pid = last_cmd(start, env, prev_pipe);
	while (nb_cmd--)
	{
		if (waitpid(-1, &status, 0) == last_pid)
			exit_code = status;
	}
	sig_in_parent(2);
	if (WIFEXITED(exit_code))
		exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}

int	pipex(t_token *token, t_env *env)
{
	t_token	*copy;
	int		exit_code;
	int		prev_pipe;
	int		nb_cmd;
	bool	flag;

	prev_pipe = -1;
	nb_cmd = 0;
	copy = token;
	exit_code = 0;
	flag = false;
	while (copy)
	{
		if (copy->type == PIPE)
		{
			nb_cmd++;
			flag = true;
		}
		copy = copy->next;
	}
	if (flag == true)
		return (exec_pipes(token, env, &prev_pipe, nb_cmd + 1));
	exit_code = exec_simple_cmd(token, env);
	return (exit_code);
}
