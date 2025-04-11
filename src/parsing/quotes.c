/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:53:56 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/11 16:15:33 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

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
