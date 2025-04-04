/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:33:06 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/04 17:19:22 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

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

void	children(int *pipefd, char **argv, char **envp)
{
	int	fd;

	fd = open (argv[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("openchildren");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("children dup2 stdout");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("children dup2 stdin");
		exit(EXIT_FAILURE);
	}
	close (pipefd[0]);
	close (pipefd[1]);
	close (fd);
	ft_exec(argv[2], envp);
}

void	parents(int *pipefd, char **argv, char **envp)
{
	int	fd;

	fd = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("openparents");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("parents dup2 stdin");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("parents dup2 stdout");
		exit(EXIT_FAILURE);
	}
	close (pipefd[1]);
	close (pipefd[0]);
	close (fd);
	ft_exec(argv[3], envp);
}

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

int	pipex(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	child;
	int		exit_code;
	int		i;

	exit_code = 0;
	i = 2;
	if (envp == NULL)
		errors(1);
	if (pipe(pipefd) == -1)
		errors(2);
	if (argc == 5)
	{
		child = fork();
		if (child < 0)
			errors(3);
		if (child == 0)
			children(pipefd, argv, envp);
		else
		{
			while (i < argc - 2)
			{
				x_cmd(argv[i], envp);
				i++;
			}
			parents(pipefd, argv, envp);
			exit_code = exit_status(child);
		}
	}
	else
		errors(4);
	print_last_status("$?", exit_code);
	return (0);
}
