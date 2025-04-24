/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiao <ymiao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:08:29 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/24 19:18:52 by ymiao            ###   ########.fr       */
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

int	ft_echo(t_cmd *cmd)
{
	int		new_line;
	int		count;

	new_line = 1;
	count = 0;
	while (cmd->argv[count])
		count++;
	if (count == 1)
		return (printf("\n"), 0);
	count = 1;
	while (cmd->argv[count] && if_n(cmd->argv[count]))
	{
		new_line = 0;
		count++;
	}
	while (cmd->argv[count])
	{
		printf("%s", cmd->argv[count]);
		if (cmd->argv[count + 1])
			printf(" ");
		count++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
