/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:19:26 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 15:24:36 by ymiao            ###   ########.fr       */
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

int	update_state(int *state, char *str, int *i)
{
	int	tmp_state;

	tmp_state = *state;
	if (str[*i] == '"' && *state == ST_GENERAL)
		*state = ST_IN_DQ;
	else if (str[*i] == '\'' && *state == ST_GENERAL)
		*state = ST_IN_SQ;
	else if (str[*i] == '"' && *state == ST_IN_DQ)
		*state = ST_GENERAL;
	else if (str[*i] == '\'' && *state == ST_IN_SQ)
		*state = ST_GENERAL;
	if (tmp_state != *state)
	{
		(*i)++;
		return (0);
	}
	if ((*state == ST_IN_DQ || *state == ST_GENERAL)
		&& str[*i] == '$' && str[*i + 1])
	{
		if (utils_update_state(*state, str[*i + 1]))
			return (utils_update_state(*state, str[*i + 1]));
	}
	return (UPDATE_WORD);
}
