/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:53:56 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/02 14:53:30 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

/*
void	ctrl_d(char *s)
{
	if (s == NULL)
	{
		printf("exit\n");
		// free all
		exit(0);
	}
}
*/

int	empty_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i == ft_strlen(str));
}

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
		{
			if (str[i] == '$')
				return (0);
			double_quotes = !double_quotes;
		}
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
