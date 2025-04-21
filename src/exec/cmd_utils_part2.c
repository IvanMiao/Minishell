/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:53:24 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/21 15:51:53 by ymiao            ###   ########.fr       */
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
			if (token->type == R_REDIRECTION)
				fd = open_file(res, 4);
			else
				fd = open_file(res, 3);
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
	char	*delimiter;
	
	delimiter = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == R_DELIMITER && token->next
			&& token->next->type == INFILE)
			delimiter = token->next->str;
		token = token->next;
	}
	return (delimiter);
}
