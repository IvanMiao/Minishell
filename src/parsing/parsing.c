/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:53:56 by cgerner           #+#    #+#             */
/*   Updated: 2025/03/31 17:37:59 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include <stdio.h>
#include <stdlib.h>

void	ctrl_d(char *s)
{
	if (s == NULL)
	{
		printf("exit\n");
		// free all
		exit(0);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

int	if_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo(int argc, char **argv)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (i < argc && if_n(argv[i]))
	{
		new_line = 0;
		i ++;
	}
	while (i < argc)
	{
		write(1, argv[i], (int)ft_strlen(argv[i]));
		if (i + 1 < argc)
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
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

int	main(int ac, char **av)
{
	char	*s;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	while (1)
	{
		s = readline("minishell$ ");
		ctrl_d(s);
		printf("Entree : %s\n", s);
		for (int i = 0; s[i]; i++)
		{
		if (check_quotes(s))
			printf("Erreur guillemets\n");
		else
		{
			char *remove = remove_quotes(s);
			if (remove)
				printf("Entree : %s\nSortie : %s\n\n", s, remove);
			else
				printf("error");
		}
	}	
	}
	return (0);
}

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
