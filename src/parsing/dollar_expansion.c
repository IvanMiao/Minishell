/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:47:23 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/16 23:20:48 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

/*
	I CAN'T BELIEVE THAT I MADE IT
*/
static char	*make_token(char *dol, char *clean_word, t_shell *shell)
{
	int			i;
	int			j;
	char		*tmp;
	char		*res;

	i = 0;
	while (dol[i] == SPACE || dol[i] == TAB)
		i++;
	if (i)
	{
		if (ft_strlen(clean_word) != 0)
			token_lstadd_back(&(shell->token), token_lst(clean_word, WORD, 0));
		free(clean_word);
		clean_word = ft_strdup("");
	}
	while (dol[i])
	{
		j = i;
		while (dol[i] && dol[i] != SPACE && dol[i] != TAB)
			i++;
		tmp = ft_substr(dol, j, i - j);
		res = ft_strjoin(clean_word, tmp);
		token_lstadd_back(&(shell->token), token_lst(res, WORD, 0));
		free(tmp);
		free(res);
		free(clean_word);
		clean_word = ft_strdup("");
		while (dol[i] && (dol[i] == SPACE || dol[i] == TAB))
			i++;
	}
	return (clean_word);
}
//printf("dollar token: %s, len: %ld\n", res, ft_strlen(res));

/*
	1) spaces in dollar var: we do make_token()
	2) no spaces: just add dollar var to clean_word
*/
static char	*decide_expand(char *dol, char *clean_word,
	int *state, t_shell *shell)
{
	char	*tmp;
	char	*res;

	if (dol && (ft_strchr(dol, SPACE) || ft_strchr(dol, TAB))
		&& *state == ST_GENERAL)
		res = make_token(dol, clean_word, shell);
	else
	{
		tmp = ft_strjoin(clean_word, dol);
		free(clean_word);
		res = tmp;
	}
	return (res);
}
// printf("dollar var is: %s\n", dol);

static char	*expand_code(t_shell *shell, char *clean_word)
{
	char	*code;
	char	*res;

	code = ft_itoa(shell->exit_code);
	res = ft_strjoin(clean_word, code);
	free(code);
	free(clean_word);
	return (res);
}

/*
following the rules for environment variables
we check if there is a variable exists
if there is, there are two conditions:
	1) no spaces in dollar var: add the dollar variable to clean_word
	2) spaces in dollar var: we should make tokens inside the dollar var
if not, just return the clean_word as it is
after this function, clean_word is updated
*/
char	*expand_dollar(t_shell *shell, int *i, char *clean_word, int *state)
{
	int		j;
	char	*tmp;
	char	*dol;
	char	*res;

	(*i)++;
	if (shell->str[*i] != '_' && !ft_isalpha(shell->str[*i]))
	{
		if (shell->str[*i] == '?')
			clean_word = expand_code(shell, clean_word);
		if (!(shell->str[*i] == '\'' || shell->str[*i] == '"'))
			(*i)++;
		return (clean_word);
	}
	j = *i;
	while (shell->str[*i]
		&& (shell->str[*i] == '_'
			|| ft_isalpha(shell->str[*i]) || ft_isdigit(shell->str[*i])))
		(*i)++;
	tmp = ft_substr(shell->str, j, (*i) - j);
	dol = ft_get_env(shell->env, tmp);
	free(tmp);
	if (!dol)
		return (clean_word);
	res = decide_expand(dol, clean_word, state, shell);
	return (res);
}

/* if no dollar sign is found,
	and the current state tells us to add a character
	we call this function*/
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
