/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:32 by cgerner           #+#    #+#             */
/*   Updated: 2025/05/01 10:40:48 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

static int	close_x_cmd(int *prev_pipe, int *pipe_fd, t_cmd *cmd)
{
	sig_in_parent(1);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
	return (free_cmd(cmd), 0);
}

static int	x_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	int		pipe_fd[2];
	pid_t	child;
	t_cmd	*cmd;
	int		exit_code;

	cmd = set_cmd(token, env, prev_pipe);
	exit_code = check_cmd(cmd, token, env);
	if (exit_code != -1)
		return (free_cmd(cmd), exit_code);
	handle_here_doc(token, env, cmd);
	if (pipe(pipe_fd) == -1)
		errors(2, token, env, cmd);
	child = fork();
	if (child == -1)
		errors(3, token, env, cmd);
	if (child == 0)
	{
		sig_in_child();
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			errors(1, token, env, cmd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec_child(token, env, cmd, prev_pipe);
	}
	return (close_x_cmd(prev_pipe, pipe_fd, cmd));
}

static int	handle_last_command(t_token *start, t_env *env,
		int *prev_pipe, int nb_cmd)
{
	pid_t	last_pid;
	int		status;
	int		exit_code;

	last_pid = last_cmd(start, env, prev_pipe);
	while (nb_cmd--)
	{
		if (waitpid(-1, &status, 0) == last_pid)
			exit_code = status;
	}
	sig_in_parent(2);
	if (access("./.heredoc.tmp", F_OK) == 0)
		unlink("./.heredoc.tmp");
	if (WIFSIGNALED(exit_code))
		return (printf("\n"), 128 + WTERMSIG(status));
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (exit_code);
}

int	exec_pipes(t_token *token, t_env *env, int *prev_pipe, int nb_cmd)
{
	t_token	*start;
	int		exit_code;

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
	exit_code = handle_last_command(start, env, prev_pipe, nb_cmd);
	return (exit_code);
}

int	pipex(t_token *token, t_env *env, t_shell *shell)
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
	exit_code = exec_simple_cmd(token, env, shell);
	return (exit_code);
}
