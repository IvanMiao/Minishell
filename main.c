/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgerner <cgerner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:16:03 by cgerner           #+#    #+#             */
/*   Updated: 2025/04/15 11:40:41 by cgerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/src.h"

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

int	check_main(t_token **token, char *history)
{
	if (!*token || empty_line(history))
	{
		if (*token)
			token_lstclear(token);
		free(history);
		return (1);
	}
	if (check_syntax(*token))
	{
		token_lstclear(token);
		free(history);
		return (1);
	}
	return (0);
}

int	exit_history(int value)
{
	rl_clear_history();
	return (value);
}

static void	print_token(t_token *token)
{
	int	i;

	i = 1;
	while (token)
	{
		printf("Token[%d] : [%s] (type %d, value %d)\n",
			i, token->str, token->type, token->value);
		token = token->next;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*history;
	t_env	*env;
	t_token	*token;

	(void)argc;
	(void)argv;
	controls();
	env = set_env(envp);
	while (1)
	{
		history = readline("minishell$ ");
		if (!history)
			exit_history(1);
		ctrl_d(history, env);
		add_history(history);
		token = init_tokens(history, env);
		if (!token)
			print_token(token);
		if (check_main(&token, history))
			continue ;
		pipex(token, env);
		token_lstclear(&token);
		free(history);
	}
	env_free(env);
	return (0);
}
