/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:33:57 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/09 04:44:43 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	check_command(t_token *token)
{
	t_token	*last;
	char	*msg;

	msg = "bash: syntax error near unexpected token ";
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!last || !token->next || token->next->type == PIPE)
				return (printf("%s`|'\n", msg), 2);
		}
		if (token->type == R_IN || token->type == R_OUT
			|| token->type == R_DELIMITER || token->type == R_REDIRECTION
			|| (token->type == R_IN && token->next->type == R_OUT)
			|| (token->type == R_DELIMITER
				&& token->next->type == R_REDIRECTION))
		{
			if (!last || !token->next)
				return (printf("%s`newline'\n", msg), 2);
		}
		last = token;
		token = token->next;
	}
	return (0);
}

int	check_command_in(t_token *token)
{
	t_token	*last;

	while (token)
	{
		if (token->type == R_IN)
		{
			if (!last || !token->next || token->next->type == R_IN)
				return (printf
					("bash: syntax error near unexpected token `<'\n"), 2);
			if (!last || !token->next || token->next->type == R_DELIMITER)
				return (printf
					("bash: syntax error near unexpected token `<<'\n"), 2);
		}
		last = token;
		token = token->next;
	}
	return (0);
}

int	check_command_out(t_token *token)
{
	t_token	*last;

	while (token)
	{
		if (token->type == R_OUT)
		{
			if (!last || !token->next || token->next->type == R_OUT)
				return (printf
					("bash: syntax error near unexpected token `>'\n"), 2);
			if (!last || !token->next || token->next->type == R_REDIRECTION)
				return (printf
					("bash: syntax error near unexpected token `>>'\n"), 2);
		}
		last = token;
		token = token->next;
	}
	return (0);
}

int	check_command_delimiter(t_token *token)
{
	t_token	*last;

	while (token)
	{
		if (token->type == R_DELIMITER)
		{
			if (!last || !token->next || token->next->type == R_DELIMITER)
				return (printf
					("bash: syntax error near unexpected token `<<'\n"), 2);
			if (!last || !token->next || token->next->type == R_IN)
				return (printf
					("bash: syntax error near unexpected token `<'\n"), 2);
		}
		last = token;
		token = token->next;
	}
	return (0);
}

int	check_command_redirection(t_token *token)
{
	t_token	*last;

	while (token)
	{
		if (token->type == R_REDIRECTION)
		{
			if (!last || !token->next || token->next->type == R_REDIRECTION)
				return (printf
					("bash: syntax error near unexpected token `>>'\n"), 2);
			if (!last || !token->next || token->next->type == R_OUT)
				return (printf
					("bash: syntax error near unexpected token `>'\n"), 2);
		}
		last = token;
		token = token->next;
	}
	return (0);
}
