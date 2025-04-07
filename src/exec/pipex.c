/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:32 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 17:43:42 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

int	exit_status(pid_t child)
{
	int	status;

	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

void	print_last_status(char *str, int value)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
		{
			printf("%d\n", value);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

void	x_cmd(t_token *token, t_env *env)
{
	int		pipe_fd2[2];
	pid_t	child;

	if (pipe(pipe_fd2) == -1)
		errors(2);
	child = fork();
	if (child == -1)
		errors(3);
	if (child == 0)
	{
		close(pipe_fd2[0]);
		if (dup2(pipe_fd2[1], STDOUT_FILENO) == -1)
			errors(1);
		close(pipe_fd2[1]);
		exec_simple_cmd(token, env);
	}
	close(pipe_fd2[1]);
	if (dup2(pipe_fd2[0], STDIN_FILENO) == -1)
		errors(1);
	close(pipe_fd2[0]);
}

int	pipex(t_token *token, t_env *env, t_cmd *cmd)
{
	t_token	*start;
	pid_t	last_cmd;
	int		exit_code;

	start = token;
	exit_code = 0;
	while (token)
	{
		if (token->type == PIPE)
		{
			x_cmd(start, env);
			token = token->next;
			start = token;
		}
		else
			token = token->next;
	}
	last_cmd = fork();
	if (last_cmd == 0)
	{
		exec_simple_cmd(start, env);
		exit(1);
	}
	exit_status(last_cmd);
	print_last_status("$?", exit_code);
	return (exit_code);
}
