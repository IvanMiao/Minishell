/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:53:56 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/14 03:42:32 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

//Lorsqu'on fait single_quote = !single_quote, ca fonctionne comme un
//interupteur. C'est-a-dire que s'il rentre une fois dans le if, il aura la
//valeur de 1, et s'il re-rentre dedans apres, il aura la valeur de 0.
//Donc si une des deux variables est encore egale a 1 lors du return, c'est
//une erreur.
int	check_quotes(char *str)
{
	int	single_quote;
	int	double_quotes;
	int	i;

	single_quote = 0;
	double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quotes)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quotes = !double_quotes;
		i++;
	}
	return (single_quote || double_quotes);
}

/*
following the rules for environment variables
we check if there is a variable exists
if there is, add the dollar variable to clean_word
if not, just return the clean_word as it is
after this function, clean_word is updated
*/
char	*expand_dollar(char *str, int *i, t_env *env, char *clean_word)
{
	int		j;
	char	*tmp;
	char	*res;

	(*i)++;
	if (str[*i] != '_' && !ft_isalpha(str[*i]))
	{
		if (!(str[*i] == '\'' || str[*i] == '"'))
			(*i)++;
		return (clean_word);
	}
	j = *i;
	while (str[*i]
		&& (str[*i] == '_' || ft_isalpha(str[*i]) || ft_isdigit(str[*i])))
		(*i)++;
	tmp = ft_substr(str, j, (*i) - j);
	res = ft_get_env(env, tmp);
	free(tmp);
	if (res)
	{
		tmp = ft_strjoin(clean_word, res);
		free(clean_word);
		clean_word = tmp;
	}
	return (clean_word);
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

/* DEEPTHOUGHT of the state machine*/
static int	utils_update_state(int state, char c)
{
	if (!(c == '_' || ft_isalpha(c) || ft_isdigit(c)))
		return (UPDATE_WORD);
	if ((c != '\'' && c != '"'))
		return (EXPAND_DOLLAR);
	if ((state == ST_GENERAL && (c == '\'' || c == '"')))
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

/*
char	*remove_quotes(char *str)
{
	char	*result;
	int		single_quote;
	int		double_quotes;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	single_quote = 0;
	double_quotes = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !double_quotes)
			single_quote = !single_quote;
		else if (str[i] == '"' && !single_quote)
			double_quotes = !double_quotes;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*keep_string_quotes(char *str, int *i)
{
	char	*result;
	char	quote;
	int		start;
	int		end;

	quote = str[*i];
	if (str[*i] == quote)
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	end = *i;
	result = ft_substr(str, start, end - start);
	if (str[*i] == quote)
		(*i)++;
	return (result);
}
*/

/*void test_keep_string_quotes(char *input)
{
	int i = 0;
	char *res = keep_string_quotes(input, &i);
	printf("Input:    %s\n", input);
	printf("Extract:  %s\n", res ? res : "(null)");
	printf("Index:    %d\n", i);
	printf("---------------------\n");
	free(res);
}

int	main(void)
{
	test_keep_string_quotes("\"hello                               world\"");
	test_keep_string_quotes("'abc def'");
	test_keep_string_quotes("\"no end");
	test_keep_string_quotes("''");
	test_keep_string_quotes("\"\"");
	test_keep_string_quotes("'123'");
	return 0;
}*/

/*
int	main(void)
{
	char	*str;
	char	*cleaned;

	while (1)
	{
		str = readline("minishell> ");
		ctrl_d(str);
		if (empty_line(str))
			printf("Ligne vide.\n");
		else if (check_quotes(str))
			printf("Erreur : Citations non fermées.\n");
		else
		{
			cleaned = remove_quotes(str);
			printf("Sans guillemets : %s\n", cleaned);
			free(cleaned);
		}
		free(str);
	}
	return (0);
}*/

/*
int	main(void)
{
	char	*str[] = {
		"\"Hello world\"",
		"'Hel'lo world'",
		"'Single' and \"double\" quotes",
		NULL
	};

	for (int i = 0; str[i] != NULL; i++)
	{
		printf("Entree : %s\n", str[i]);
		if (check_quotes(str[i]))
			printf("Erreur guillemets\n");
		else
		{
			char *remove = remove_quotes(str[i]);
			if (remove)
				printf("Entree : %s\nSortie : %s\n\n", str[i], remove);
			else
				printf("error");
		}
	}	
	return 0;
}*/
