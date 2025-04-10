/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:02:51 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/10 15:29:58 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src.h"

int	exit_status(pid_t child)
{
	int	status;

	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

void	print_last_status(t_token *token, int value)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if (token->type == DOLLAR && token->str[i + 1]
			&& token->str[i + 1] == '?')
		{
			printf("%d\n", value);
			i += 2;
		}
		else
		{
			write(1, &token->str[i], 1);
			i++;
		}
	}
}

/*int	main(void)
{
	pid_t	pid = fork();
	int		status;

	if (pid == 0)
		exit(42);
	else
	{
		status = exit_status(pid);
		t_token token;
		token.str = "Le status est: $? !";
		token.type = DOLLAR;

		print_last_status(&token, status);
	}

	return (0);
}*/
