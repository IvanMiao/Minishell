/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:32 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/10 12:07:44 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

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
		if (str[i] == DOLLAR && str[i + 1] && str[i + 1] == '?')
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
		printf(RED"avant le dup2\n"ENDCOLOR);
		if (dup2(pipe_fd2[1], STDOUT_FILENO) == -1)
			errors(1);
		printf("apres le dup2\n");
		close(pipe_fd2[1]);
		ft_exec(token, env, pipe_fd2);
	}
	close(pipe_fd2[1]);
	if (dup2(pipe_fd2[0], STDIN_FILENO) == -1)
		errors(1);
	close(pipe_fd2[0]);
}

int	pipex(t_token *token, t_env *env)
{
	t_token	*start;
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
	exit_code = exec_simple_cmd(start, env);
	print_last_status("$?", exit_code);
	return (exit_code);
}
