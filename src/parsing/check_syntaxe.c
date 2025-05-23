/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:33:57 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/22 16:35:44 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	check_pipe(t_token *token)
{
	t_token	*last;
	char	*msg;

	msg = "minishell: syntax error near unexpected token ";
	last = NULL;
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!last || !token->next || token->next->type == PIPE
				|| (last->type >= R_IN && last->type <= R_REDIRECTION))
				return (ft_fprintf(2, "%s`|'\n", msg), 2);
		}
		last = token;
		token = token->next;
	}
	return (0);
}

int	check_redir_in_delim(t_token *token, char *msg)
{
	while (token)
	{
		if (token->type == R_IN)
		{
			if (!token->next)
				return (ft_fprintf(2, "%s`newline'\n", msg), 2);
			if (token->next->type == R_IN)
				return (ft_fprintf(2, "%s`<'\n", msg), 2);
			if (token->next->type == R_DELIMITER)
				return (ft_fprintf(2, "%s`<<'\n", msg), 2);
		}
		else if (token->type == R_DELIMITER)
		{
			if (!token->next)
				return (ft_fprintf(2, "%s`newline'\n", msg), 2);
			else if (token->next->type == R_IN)
				return (ft_fprintf(2, "%s`<'\n", msg), 2);
			else if (token->next->type == R_DELIMITER)
				return (ft_fprintf(2, "%s`<<'\n", msg), 2);
		}
		token = token->next;
	}
	return (0);
}

int	check_redir_out_append(t_token *token, char *msg)
{
	while (token)
	{
		if (token->type == R_OUT)
		{
			if (!token->next)
				return (ft_fprintf(2, "%s`newline'\n", msg), 2);
			if (token->next->type == R_OUT)
				return (ft_fprintf(2, "%s`>'\n", msg), 2);
			if (token->next->type == R_REDIRECTION)
				return (ft_fprintf(2, "%s`>>'\n", msg), 2);
		}
		else if (token->type == R_REDIRECTION)
		{
			if (!token->next)
				return (ft_fprintf(2, "%s`newline'\n", msg), 2);
			if (token->next->type == R_REDIRECTION)
				return (ft_fprintf(2, "%s`>>'\n", msg), 2);
			if (token->next->type == R_OUT)
				return (ft_fprintf(2, "%s`>'\n", msg), 2);
		}
		token = token->next;
	}
	return (0);
}

int	check_syntax(t_token *token)
{
	char	*msg;

	msg = "minishell: syntax error near unexpected token ";
	if (check_pipe(token))
		return (2);
	if (check_redir_in_delim(token, msg))
		return (2);
	if (check_redir_out_append(token, msg))
		return (2);
	return (0);
}
