/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:08:29 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/04 16:17:51 by cgerner          ###   ########.fr       */
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


int	main(int argc, char **argv)
{
	ft_echo(argc, argv);
	return (0);
}

