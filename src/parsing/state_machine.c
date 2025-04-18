/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:19:26 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/18 02:34:03 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

/* DEEPTHOUGHT of the state machine*/
static int	expand_or_not(int state, char c)
{
	if (!(c == '_' || ft_isalpha(c) || ft_isdigit(c)))
	{
		if ((state == ST_GENERAL && (c == '\'' || c == '"' || c == '?')))
			return (EXPAND_DOLLAR);
		else if (state == ST_IN_DQ && c == '?')
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
	if (tmp_state != *state)
	{
		if (!last_token || last_token->type != R_DELIMITER)
		{
			(*i)++;
			return (0);
		}
		return (UPDATE_WORD);
	}
	if ((*state == ST_IN_DQ || *state == ST_GENERAL)
		&& shell->str[*i] == '$' && shell->str[*i + 1]
		&& (!last_token || last_token->type != R_DELIMITER))
	{
		if (expand_or_not(*state, shell->str[*i + 1]))
			return (expand_or_not(*state, shell->str[*i + 1]));
	}
	return (UPDATE_WORD);
}

/* if no dollar sign is found,
	and the current state tells us to add a character
	we call this function */
char	*update_clean_word(char *clean_word, char *str, int *i)
{
	char	tmp[2];
	char	*res;

	tmp[0] = str[*i];
	tmp[1] = '\0';
	res = ft_strjoin(clean_word, tmp);
	free(clean_word);
	return (res);
}
