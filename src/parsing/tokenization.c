/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:45 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/14 17:26:22 by ymiao            ###   ########.fr       */
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

void	modif_tokens_2(char *str, int *i, t_token **token, t_env *env)
{
	int			state;
	char		*clean_word;
	t_tokentype	type;
	int			order;

	state = ST_GENERAL;
	clean_word = ft_strdup("");
	while (str[*i])
	{
		if (state == ST_GENERAL && (str[*i] == '|' || str[*i] == '<'
				|| str[*i] == '>' || str[*i] == ' ' || str[*i] == '\t'))
			break ;
		order = update_state(&state, str, i);
		if (order == EXPAND_DOLLAR)
			clean_word = expand_dollar(str, i, env, clean_word);
		else if (order == UPDATE_WORD)
		{
			clean_word = update_clean_word(clean_word, str, i);
			(*i)++;
		}
	}
	type = assign_tokens(clean_word, token_lstlast(*token));
	if (!(order == EXPAND_DOLLAR && ft_strlen(clean_word) == 0))
		token_lstadd_back(token, token_lst(clean_word, type, 0));
	free(clean_word);
}
//printf("char: %c, state: %d\n", str[*i], state);

void	modif_tokens(char *str, int *i, t_token **token, t_env *env)
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
		token_lstadd_back(token, token_lst(operation, type, 0));
		free(operation);
		*i += length_op;
	}
	else
		modif_tokens_2(str, i, token, env);
}

//Pas sur de l'affichage du 1er perror
t_token	*init_tokens(char *str, t_env *env)
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
		modif_tokens(str, &i, &token, env);
	return (token);
}

/*
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
