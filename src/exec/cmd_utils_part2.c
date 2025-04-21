/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:53:24 by ymiao             #+#    #+#             */
/*   Updated: 2025/04/21 17:15:58 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*get_infile(t_token *token)
{
	char	*res;

	res = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == R_IN && token->next && token->next->type == INFILE)
			res = token->next->str;
		token = token->next;
	}
	return (res);
}

char	*get_outfile(t_token *token)
{
	char	*res;
	int		fd;

	res = NULL;
	while (token && token->type != PIPE)
	{
		if ((token->type == R_OUT || token->type == R_REDIRECTION)
			&& token->next && token->next->type == OUTFILE)
		{
			res = token->next->str;
			if (token->type == R_REDIRECTION)
				fd = open_file(res, 4);
			else
				fd = open_file(res, 3);
			close(fd);
		}
		token = token->next;
	}
	return (res);
}

bool	check_append(t_token *token)
{
	bool	res;

	res = false;
	while (token && token->type != PIPE)
	{
		if (token->type == R_OUT && token->next && token->next->type == OUTFILE)
			res = false;
		if (token->type == R_REDIRECTION && token->next
			&& token->next->type == OUTFILE)
			res = true;
		token = token->next;
	}
	return (res);
}

char	**get_delimiter(t_token *token)
{
	char	**delimiter;
	int		count;
	t_token	*tmp;

	delimiter = NULL;
	count = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == R_DELIMITER && tmp->next
			&& tmp->next->type == INFILE)
			count++;
		tmp = tmp->next;
	}
	if (count == 0)
		return (NULL);
	delimiter = malloc(sizeof(char *) * (count + 1));
	if (!delimiter)
		return (NULL);
	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == R_DELIMITER && token->next && token->next->type == INFILE)
			delimiter[count++] = ft_strdup(token->next->str);
		token = token->next;
	}
	delimiter[count] = NULL;
	return (delimiter);
}
