/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:25:46 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/15 15:55:26 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

char	*if_options(char *str)
{
	static char	options[3];

	if (str[0] == '-' && str[1])
	{
		options[0] = '-';
		options[1] = str[1];
		options[2] = '\0';
		return (options);
	}
	return (0);
}

int	ft_pwd(char **argv)
{
	char	buffer[1024];
	char	*invalid;

	if (argv[1])
	{
		invalid = if_options(argv[1]);
		if (invalid)
		{
			ft_fprintf(2, "minishell: pwd: %s: invalid option\n", invalid);
			return (2);
		}
	}
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
	{
		perror("pwd error");
		return (1);
	}
	return (0);
}

/*
int	main(void)
{
	ft_pwd();
	return (0);
}
*/
