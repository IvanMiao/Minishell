/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:24:32 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 14:10:04 by cgerner          ###   ########.fr       */
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

void	x_cmd(char *cmd, char **envp)
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
		ft_exec(cmd, envp);
	}
	close(pipe_fd2[1]);
	if (dup2(pipe_fd2[0], STDIN_FILENO) == -1)
		errors(1);
	close(pipe_fd2[0]);
}

int	pipex(t_token *token, t_env *env)
{
	int		pipefd[2];
	pid_t	child;
	int		exit_code;
	int		i;

	exit_code = 0;
	i = 2;
	if (env == NULL)
		errors(1);
	if (pipe(pipefd) == -1)
		errors(2);
	child = fork();
	if (child < 0)
		errors(3);
	if (child == 0)
		children(pipefd, argv, env);
	else
	{
		while (i < argc - 2)
		{
			x_cmd(argv[i], env);
			i++;
		}
		parents(pipefd, argv, env);
		exit_code = exit_status(child);
	}
	errors(4);
	print_last_status("$?", exit_code);
	return (0);
}
