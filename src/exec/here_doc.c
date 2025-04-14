/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:36:33 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/14 18:55:10 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

void	read_here_doc(char *limiter)
{
	char	*str;
	int		fd;

	fd = open("./.heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		str = readline("> ");
		if (ft_strlen(str) == ft_strlen(limiter)
			&& ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_fprintf(fd, "%s\n", str);
		free(str);
	}
	return ;
}

void	here_doc(t_token *token, t_env *env, t_cmd *cmd)
{
	(void) env;
	if (!token)
		return ;
	read_here_doc(cmd->delimiter);
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
