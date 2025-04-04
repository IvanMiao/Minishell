/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:48:25 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/04 13:49:05 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_charset(char s, char c)
{
	if (s == '\0')
		return (0);
	if (s == c)
		return (1);
	else
		return (0);
}

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_charset(s[i], c))
		i++;
	while (s[i])
	{
		while (!ft_charset(s[i], c) && s[i] != '\0')
			i++;
		if (s[i] == '\0' || ft_charset(s[i], c))
			count++;
		while (ft_charset(s[i], c) && s[i] != '\0')
			i++;
	}
	return (count);
}

int	one_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !ft_charset(s[i], c))
		i++;
	return (i);
}

void	ft_split2(char **s, int j)
{
	int	i;

	i = 0;
	if (s[j] == NULL)
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (tab == NULL)
		return (0);
	while (s[i] && j < ft_count_words(s, c))
	{
		while (s[i] != '\0' && ft_charset(s[i], c))
			i++;
		if (s[i] && !ft_charset(s[i], c))
		{
			tab[j] = ft_substr(s, i, one_word(s + i, c));
			ft_split2(tab, j);
			j++;
		}
		while (s[i] != '\0' && !ft_charset(s[i], c))
			i++;
	}
	tab[j] = NULL;
	return (tab);
}