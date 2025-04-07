/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:53:24 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/07 17:22:14 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*get_infile(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == R_IN && token->next && token->next->type == INFILE)
			return (token->next->str);
		token = token->next;
	}
	return (NULL);
}

char	*get_outfile(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if ((token->type == R_OUT || token->type == R_REDIRECTION)
			&& token->next && token->next->type == OUTFILE)
			return (token->next->str);
		token = token->next;
	}
	return (NULL);
}

bool	check_append(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == R_REDIRECTION && token->next && token->next->type == OUTFILE)
			return (true);
		token = token->next;
	}
	return (false);
}

char	*get_delimiter(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == R_DELIMITER && token->next && token->next->type == INFILE)
			return (token->next->str);
		token = token->next;
	}
	return (NULL);
}