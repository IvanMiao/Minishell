/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:53:24 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/18 03:05:12 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*get_infile(t_token *token)
{
	char	*res;

	res = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == R_IN && token->next && token->next->type == INFILE)
			res = token->next->str;
		token = token->next;
	}
	return (res);
}

char	*get_outfile(t_token *token)
{
	char	*res;
	int		fd;

	res = NULL;
	while (token && token->type != PIPE)
	{
		if ((token->type == R_OUT || token->type == R_REDIRECTION)
			&& token->next && token->next->type == OUTFILE)
		{
			res = token->next->str;
			fd = open_file(res, 1);
			close(fd);
		}
		token = token->next;
	}
	return (res);
}

bool	check_append(t_token *token)
{
	bool	res;

	res = false;
	while (token && token->type != PIPE)
	{
		if (token->type == R_OUT && token->next && token->next->type == OUTFILE)
			res = false;
		if (token->type == R_REDIRECTION && token->next
			&& token->next->type == OUTFILE)
			res = true;
		token = token->next;
	}
	return (res);
}

char	*get_delimiter(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == R_DELIMITER && token->next
			&& token->next->type == INFILE)
			return (token->next->str);
		token = token->next;
	}
	return (NULL);
}

int	is_directory(t_cmd *cmd)
{
	struct stat	info;

	if (stat(cmd->pathname, &info) != 0
		|| access(cmd->pathname, F_OK) != 0)
		return (1);
	return (0);
}
