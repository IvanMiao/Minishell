/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:32 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/10 15:04:25 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	x_cmd(t_token *token, t_env *env, int *prev_pipe)
{
	int		pipe_fd[2];
	pid_t	child;

	if (pipe(pipe_fd) == -1)
		errors(2);
	child = fork();
	if (child == -1)
		errors(3);
	if (child == 0)
	{
		if (*prev_pipe != 0)
		{
			if (dup2(*prev_pipe, STDIN_FILENO) == -1)
				errors(1);
			close(*prev_pipe);
		}
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			errors(1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		ft_exec(token, env);
		exit(1);
	}
	if (*prev_pipe != 0)
		close(*prev_pipe);
	close(pipe_fd[1]);
	*prev_pipe = pipe_fd[0];
}

int	pipex(t_token *token, t_env *env)
{
	t_token	*start;
	int		exit_code;
	int		prev_pipe;

	prev_pipe = 0;
	start = token;
	exit_code = 0;
	while (token)
	{
		if (token->type == PIPE)
		{
			x_cmd(start, env, &prev_pipe);
			token = token->next;
			start = token;
		}
		else
			token = token->next;
	}
	exit_code = exec_simple_cmd(start, env, &prev_pipe);
	return (exit_code);
}
