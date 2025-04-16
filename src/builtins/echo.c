/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:08:29 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/16 23:23:54 by ymiao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

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
			return (i);
		if (str[i] == SPACE || str[i] == TAB)
			return (i + 1);
	}
	return (0);
}

int	ft_echo(t_token *token)
{
	int		new_line;
	t_token	*copy;

	new_line = 1;
	if (token->next == NULL)
		return (printf("\n"), 0);
	copy = token->next;
	while (copy && (copy->type == WORD || copy->type == DOLLAR)
		&& if_n(copy->str))
	{
		new_line = 0;
		copy = copy->next;
	}
	while (copy && (copy->type == WORD || copy->type == DOLLAR))
	{
		printf("%s", copy->str);
		if (copy->next
			&& ((copy->next->type == WORD || copy->next->type == DOLLAR)))
			printf(" ");
		copy = copy->next;
	}
	if (new_line)
		printf("\n");
	return (0);
}
