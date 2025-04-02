/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:33:57 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/02 14:53:36 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	check_command(t_token *token)
{
	t_token	*last;

	while (token)
	{
		if (token->type == PIPE)
		{
			if (!last || !token->next || token->next->type == PIPE)
				return (printf(
						"bash: syntax error near unexpected token `|'\n"), 0);
		}
		if (token->type == R_IN || token->type == R_OUT
			|| token->type == R_DELIMITER || token->type == R_REDIRECTION)
		{
			if (!last || !token->next || token->next->type == R_IN
				|| token->next->type == R_OUT
				|| token->next->type == R_DELIMITER
				|| token->next->type == R_REDIRECTION)
				return (printf
					("bash: syntax error near unexpected token `newline'\n"), 0);
		}
		last = token;
		token = token->next;
	}
	return (1);
}

/*
int	check_command_2(t_token *token)
{
	t_token	*last;

	while (token)
	{
		
	}
}
*/