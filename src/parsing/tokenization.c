/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:45 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/16 16:44:24 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

static bool	meet_end_char(t_shell *shell, int *i)
{
	return (shell->str[*i] == '|' || shell->str[*i] == '<'
		|| shell->str[*i] == '>' || shell->str[*i] == ' '
		|| shell->str[*i] == '\t');
}

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

void	modif_tokens_2(t_shell *shell, int *i)
{
	int			state;
	char		*clean_word;
	t_tokentype	type;
	int			order;

	state = ST_GENERAL;
	clean_word = ft_strdup("");
	while (shell->str[*i])
	{
		if (state == ST_GENERAL && meet_end_char(shell, i))
			break ;
		order = update_state(&state, shell, i);
		if (order == EXPAND_DOLLAR)
			clean_word = expand_dollar(shell, i, clean_word, &state);
		else if (order == UPDATE_WORD)
		{
			clean_word = update_clean_word(clean_word, shell->str, i);
			(*i)++;
		}
	}
	type = assign_tokens(clean_word, token_lstlast(shell->token));
	if (!(order == EXPAND_DOLLAR && ft_strlen(clean_word) == 0))
		token_lstadd_back(&(shell->token), token_lst(clean_word, type, 0));
	free(clean_word);
}
//printf("char: %c, state: %d\n", str[*i], state);

void	modif_tokens(t_shell *shell, int *i)
{
	int			length_op;
	char		*operation;
	t_tokentype	type;
	t_token		*last_token;

	while (shell->str[*i] == ' ' || shell->str[*i] == '\t')
		(*i)++;
	if (shell->str[*i] == '\0')
		return ;
	if (shell->str[*i] == '|' || shell->str[*i] == '<' || shell->str[*i] == '>')
	{
		length_op = 1;
		if (shell->str[*i + 1] == shell->str[*i]
			&& (shell->str[*i] == '<' || shell->str[*i] == '>'))
			length_op = 2;
		operation = ft_substr(shell->str, *i, length_op);
		last_token = token_lstlast(shell->token);
		type = assign_tokens(operation, last_token);
		token_lstadd_back(&(shell->token), token_lst(operation, type, 0));
		free(operation);
		*i += length_op;
	}
	else
		modif_tokens_2(shell, i);
}

//Pas sur de l'affichage du 1er perror
t_token	*init_tokens(t_shell *shell)
{
	int		i;

	i = 0;
	shell->token = NULL;
	if (check_quotes(shell->str))
	{
		perror("Error: Unclosed quotes");
		return (NULL);
	}
	while (shell->str[i])
		modif_tokens(shell, &i);
	return (shell->token);
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
