/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:45 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/11 20:36:53 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

t_tokentype	assign_tokens(char *str, t_token *last_token)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (R_DELIMITER);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (R_REDIRECTION);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(str, "<", 1) == 0)
		return (R_IN);
	if (ft_strncmp(str, ">", 1) == 0)
		return (R_OUT);
	if (ft_strncmp(str, "$", 1) == 0)
		return (DOLLAR);
	if (last_token && (last_token->type == R_IN
			|| last_token->type == R_DELIMITER))
		return (INFILE);
	if (last_token && (last_token->type == R_OUT
			|| last_token->type == R_REDIRECTION))
		return (OUTFILE);
	return (WORD);
}

char	*update_clean_word(char *clean_word, char *str, int *i)
{
	char	*tmp;
	char	*res;
	
	tmp = malloc(sizeof(char) * 2);
	tmp[0] = str[*i];
	tmp[1] = '\0';
	res = ft_strjoin(clean_word, tmp);
	free(clean_word);
	free(tmp);
	return (res);
}

void	update_state(int *state, char *str, int *i)
{
	if (str[*i] == '"' && *state == STATE_GENERAL)
		*state = STATE_IN_DQ;
	else if (str[*i] == '\'' && *state == STATE_GENERAL)
		*state = STATE_IN_SQ;
	else if (str[*i] == '"' && *state == STATE_IN_DQ)
		*state = STATE_GENERAL;
	else if (str[*i] == '\'' && *state == STATE_IN_SQ)
		*state = STATE_GENERAL;
}

void	modif_tokens_2(char *str, int *i, t_token **token)
{
	int			state;
	char		*clean_word;
	t_tokentype	type;
	int			tmp;

	state = STATE_GENERAL;
	clean_word = ft_strdup("");
	while (str[*i])
	{
		if ((str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
			|| str[*i] == ' ' || str[*i] == '\t')
			break ;
		update_state(&state, str, i);
		if ((str[*i] == '"' && state != STATE_IN_SQ)
			|| (str[*i] == '\'' && state != STATE_IN_DQ))
			(*i)++;
		if ((str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
			|| str[*i] == ' ' || str[*i] == '\t' || !str[*i])
			break ;
		tmp = state;
		update_state(&state, str, i);
		if (tmp == state)
		{
			clean_word = update_clean_word(clean_word, str, i);
			(*i)++;
		}
			// if state == DQ, str[*i] == '$', expand
		else
			(*i)++;
	}
	type = assign_tokens(clean_word, token_lstlast(*token));
	token_lstadd_back(token, token_lst(clean_word, type, 0, false));
	free(clean_word);
}


void	modif_tokens(char *str, int *i, t_token **token)
{
	int			length_op;
	char		*operation;
	t_tokentype	type;
	t_token		*last_token;

	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '\0')
		return ;
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>')
	{
		length_op = 1;
		if (str[*i + 1] == str[*i] && (str[*i] == '<' || str[*i] == '>'))
			length_op = 2;
		operation = ft_substr(str, *i, length_op);
		last_token = token_lstlast(*token);
		type = assign_tokens(operation, last_token);
		token_lstadd_back(token, token_lst(operation, type, 0, false));
		free(operation);
		*i += length_op;
	}
	else
		modif_tokens_2(str, i, token);
}

//Pas sur de l'affichage du 1er perror
t_token	*init_tokens(char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	if (check_quotes(str))
	{
		perror("Error: Unclosed quotes");
		return (NULL);
	}
	while (str[i])
		modif_tokens(str, &i, &token);
	return (token);
}

/*
void	print_token(t_token *token)
{
	while (token)
	{
		printf("Token : [%s] (type %d, value %d)\n",
			token->str, token->type, token->value);
		token = token->next;
	}
}

int	main(void)
{
	char *str = "cat < input.txt | grep hello > output.txt";
	t_token	*token;

	printf ("Entree : %s\n", str);
	token = init_tokens(str);
	if (token)
	{
		print_token(token);
	}
	token_lstclear(&token);
	return (0);
}
*/
