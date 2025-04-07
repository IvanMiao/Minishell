/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 14:09:25 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	read_here_doc(char *limiter)
{
	int		pipe_fd[2];
	char	*str;

	if (pipe(pipe_fd) == -1)
		errors(2);
	if (fork() == 0)
	{
		close(pipe_fd[0]);
		while (1)
		{
			str = readline("> ");
			if (!str || (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
					&& str[ft_strlen(limiter)] == '\n'))
				error_here_doc(str);
			write(pipe_fd[1], str, ft_strlen(str));
			free(str);
		}
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		errors(1);
	close(pipe_fd[0]);
	wait(NULL);
}

void	here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	int	fd_in;
	int	fd_out;

	if (argc < 6)
		errors(4);
	if (ft_strncmp(argv[1], "<<", 2) == 0)
	{
		fd_out = open_file(argv[argc - 1], 2);
		read_here_doc(argv[2]);
	}
	else
	{
		fd_in = open_file(argv[1], 0);
		fd_out = open_file(argv[argc - 1], 1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	ft_exec(argv[argc - 2], envp);
}

