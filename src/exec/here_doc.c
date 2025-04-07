/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/07 15:25:20 by cgerner          ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	t_token	*start;

	if (!token || !token->next || token->type != R_DELIMITER)
		return ;
	if (token->type == R_DELIMITER)
	{
		start = token;
		cmd->delimiter = token->next->str;
		fd_out = open_file(cmd->outfile, 2);
		read_here_doc(cmd->delimiter);
		close(fd_out);
		dup2(fd_out, STDOUT_FILENO);
		exec_simple_cmd(start->str, env);
	}
}

void	handle_here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	while (token)
	{
		if (token->type == R_DELIMITER && token->next)
		{
			here_doc(token->next, env, cmd);
			break ;
		}
		token = token->next;
	}
}
