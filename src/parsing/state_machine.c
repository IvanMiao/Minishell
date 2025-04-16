/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:19:26 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 16:58:06 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

/* DEEPTHOUGHT of the state machine*/
static int	utils_update_state(int state, char c)
{
	if (!(c == '_' || ft_isalpha(c) || ft_isdigit(c)))
	{
		if ((state == ST_GENERAL && (c == '\'' || c == '"' || c == '?')))
			return (EXPAND_DOLLAR);
		return (UPDATE_WORD);
	}
	if ((c != '\'' && c != '"'))
		return (EXPAND_DOLLAR);
	return (0);
}

int	update_state(int *state, t_shell *shell, int *i)
{
	int		tmp_state;
	t_token	*last_token;

	tmp_state = *state;
	if (shell->str[*i] == '"' && *state == ST_GENERAL)
		*state = ST_IN_DQ;
	else if (shell->str[*i] == '\'' && *state == ST_GENERAL)
		*state = ST_IN_SQ;
	else if (shell->str[*i] == '"' && *state == ST_IN_DQ)
		*state = ST_GENERAL;
	else if (shell->str[*i] == '\'' && *state == ST_IN_SQ)
		*state = ST_GENERAL;
	last_token = token_lstlast(shell->token);
	if (tmp_state != *state && last_token->type != R_DELIMITER)
	{
		(*i)++;
		return (0);
	}
	if ((*state == ST_IN_DQ || *state == ST_GENERAL)
		&& shell->str[*i] == '$' && shell->str[*i + 1] && last_token->type != R_DELIMITER)
	{
		if (utils_update_state(*state, shell->str[*i + 1]))
			return (utils_update_state(*state, shell->str[*i + 1]));
	}
	return (UPDATE_WORD);
}
