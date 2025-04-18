/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:12:44 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/15 15:39:21 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	open_file(char *file, int value)
{
	int	fd;

	if (value == 0)
		fd = open(file, O_RDONLY);
	else if (value == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		ft_fprintf(2, "minishell: ", NULL);
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	error_here_doc(char *str)
{
	free(str);
	exit(EXIT_SUCCESS);
}

void	errors(int value)
{
	if (value == 1)
	{
		perror("No environment variable");
		exit(EXIT_FAILURE);
	}
	else if (value == 2)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	else if (value == 3)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (value == 4)
	{
		perror("Not enough or too much arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (value == 5)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	free_all(t_env *env, t_token *token, t_cmd *cmd)
{
	env_free(env);
	token_lstclear(&token);
	free_cmd(cmd);
}
