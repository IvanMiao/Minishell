/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:53:56 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/29 04:20:30 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"
#include "parsing.h"

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

	result = (char *)mem_manager(MALLOC ,ft_strlen(str) + 1, NULL);
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
