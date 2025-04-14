/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:02:51 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/14 15:07:09 by cgerner          ###   ########.fr       */
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

char	*alloc_exit_status(t_token *token, int exit_code)
{
	char	*result;
	char	*tmp;
	char	*code_str;
	int		i;

	result = ft_strdup("");
	code_str = ft_itoa(exit_code);
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && token->str[i + 1] == '?')
		{
			tmp = result;
			result = ft_strjoin(result, code_str);
			free(tmp);
			i += 2;
		}
		else
		{
			tmp = result;
			result = ft_strjoin_char(result, token->str[i]);
			free(tmp);
			i++;
		}
	}
	free(code_str);
	return (result);
}

void	search_code_token(t_token *token, int exit_code)
{
	t_token	*tmp;
	char	*new_str;

	tmp = token;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "$?", ft_strlen(tmp->str)))
		{
			new_str = alloc_exit_status(tmp, exit_code);
			tmp->str = new_str;
		}
		tmp = tmp->next;
	}
}

/*int main(void)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->str = " $?echo $? et encore $? ! $?";

	int exit_code = 42;

	printf("🔧 Résultat de print_last_status :\n");
	print_last_status(token, exit_code);

	printf("🔧 Résultat de  :\n");
	search_code_token(token, exit_code);
	printf("%s\n", token->str);

	return 0;
}*/

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
