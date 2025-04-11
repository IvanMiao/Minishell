/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:45 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/11 19:03:37 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	check_all_commands(t_token *token)
{
	return (check_command_in(token) || check_command_out(token)
		|| check_command_delimiter(token) || check_command_redirection(token)
		|| check_command(token));
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

char	*update_clean_word(char *clean_word, char *str, int start, int *i)
{
	char	*tmp;
	char	*res;

	tmp = ft_substr(str, start, *i - start);
	res = ft_strjoin(clean_word, tmp);
	if (ft_strlen(clean_word) != 0)
		free(clean_word);
	free(tmp);
	tmp = res;
	res = remove_quotes(res);
	free(tmp);
	return (res);
}

void	modif_tokens_2(char *str, int *i, t_token **token)
{
	int			start;
	char		*clean_word;
	char		*s_inquote;
	t_tokentype	type;
	char		*tmp;
	bool		flag;

	flag = false;
	start = *i;

	clean_word = "";

	while (str[*i])
	{
		while ((str[*i] && str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
			&& str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\'' && str[*i] != '"')
			(*i)++;
		if (!(str[*i] == '\'' || str[*i] == '"'))
			break ;
		clean_word = update_clean_word(clean_word, str, start, i);
		if (str[*i] == '\'' || str[*i] == '"')
		{
			s_inquote = keep_string_quotes(str, i);
			tmp = clean_word;
			clean_word = ft_strjoin(clean_word, s_inquote);
			free(tmp);
			free(s_inquote);
			printf(RED"QUOTE! clean_word is : %s\n"ENDCOLOR, clean_word);
			(*i)++;
			start = (*i);
		}
	}
	type = assign_tokens(clean_word, token_lstlast(*token));
	token_lstadd_back(token, token_lst(clean_word, type, 0, flag));
	free(clean_word);
}


/*
void	modif_tokens_2(char *str, int *i, t_token **token)
{
	int			start;
	char		*clean_word;
	char		*length_op;
	t_tokentype	type;
	bool		flag;

	flag = false;
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (str[*i] == '\'')
			flag = true;
		length_op = keep_string_quotes(str, i);
		clean_word = ft_strdup(length_op);
		free(length_op);
	}
	else
	{
		start = *i;
		while ((str[*i] && str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
			&& str[*i] != ' ')
			(*i)++;
		clean_word = remove_quotes(ft_substr(str, start, *i - start));
		printf(BLUE"\nclean_word is : %s\n"ENDCOLOR, clean_word);
	}
	//printf("\nclean_word is : %s\n", clean_word);
	type = assign_tokens(clean_word, token_lstlast(*token));
	token_lstadd_back(token, token_lst(clean_word, type, 0, flag));
	free(clean_word);
}
*/

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
